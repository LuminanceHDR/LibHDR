/*
 * This file is a part of LibHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2012 Davide Anastasia
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 */

#include "libhdr/io/jpegreader.h"
#include "libhdr/io/framereader.aux.h"
#include "libhdr/io/ioexceptions.h"
#include "libhdr/image.h"
#include <libhdr/details/resourcehandler.h>
#include <libhdr/details/misc.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <jpeglib.h>
#include <lcms2.h>

namespace LibHDR
{
namespace details
{

// Custom deleter for cmsHTRANSFORM
struct DeleterCmsTransform
{
    static
    void release(cmsHTRANSFORM p)
    {
        cmsDeleteTransform(p);
    }
};

// Custom deleter for cmsHPROFILE
struct DeleterCmsProfile
{
    static
    void release(cmsHPROFILE p)
    {
        cmsCloseProfile(p);
    }
};

}

namespace IO
{
using namespace std;
using namespace LibHDR::details;    // ResourceDeleter

namespace
{
inline
float to_float(const JSAMPLE& sample)
{
    return static_cast<float>(sample)/255.f;
}

inline
void fill_image(Pixel* dst, const JSAMPLE* src, const int N, const int N_COMP)
{
    for (int idx = 0; idx < N; ++idx)
    {
        *dst = Pixel(to_float(src[0]),
                       to_float(src[1]),
                       to_float(src[2])); // alpha to 1.0f, full opaque

        src += N_COMP;
        dst++;
    }
}

void error_handler(j_common_ptr cinfo)
{
    struct jpeg_decompress_struct *ptr = (struct jpeg_decompress_struct *) cinfo;
    jpeg_destroy_decompress(ptr);

    throw ReadException("JPEG:  void error_handler(j_common_ptr cinfo)");
}

void output_message(j_common_ptr cinfo)
{
    char buffer[JMSG_LENGTH_MAX];

    (*cinfo->err->format_message) (cinfo, buffer);

    struct jpeg_decompress_struct *ptr = (struct jpeg_decompress_struct *) cinfo;
    jpeg_destroy_decompress(ptr);

    throw ReadException("JPEG:  void error_handler(j_common_ptr cinfo)");
}

///////////////////////////////////////////////////////////////////////////////
//
// Code taken from iccjpeg.c from lcms distribution
// and slightly changed to use C++ data structures
//
//

const short ICC_MARKER =  (JPEG_APP0 + 2);	// JPEG marker code for ICC
const int MAX_SEQ_NO = 255;                 // sufficient since marker numbers are bytes
const unsigned int ICC_OVERHEAD_LEN = 14;            // size of non-profile data in APP2 */
const int MAX_BYTES_IN_MARKER = 65533;      // maximum data len of a JPEG marker
const int MAX_DATA_BYTES_IN_MARKER = (MAX_BYTES_IN_MARKER - ICC_OVERHEAD_LEN);

//! \brief Prepare for reading an ICC profile
void
setup_read_icc_profile(j_decompress_ptr cinfo)
{
    // Tell the library to keep any APP2 data it may find
    jpeg_save_markers(cinfo, ICC_MARKER, 0xFFFF);
}

//! \brief Handy subroutine to test whether a saved marker is an ICC profile marker.
bool
marker_is_icc(jpeg_saved_marker_ptr marker)
{
    return (marker->marker == ICC_MARKER &&
            marker->data_length >= ICC_OVERHEAD_LEN &&
            /* verify the identifying string */
            GETJOCTET(marker->data[0]) == 0x49 &&
            GETJOCTET(marker->data[1]) == 0x43 &&
            GETJOCTET(marker->data[2]) == 0x43 &&
            GETJOCTET(marker->data[3]) == 0x5F &&
            GETJOCTET(marker->data[4]) == 0x50 &&
            GETJOCTET(marker->data[5]) == 0x52 &&
            GETJOCTET(marker->data[6]) == 0x4F &&
            GETJOCTET(marker->data[7]) == 0x46 &&
            GETJOCTET(marker->data[8]) == 0x49 &&
            GETJOCTET(marker->data[9]) == 0x4C &&
            GETJOCTET(marker->data[10]) == 0x45 &&
            GETJOCTET(marker->data[11]) == 0x0);
}

bool
read_icc_profile(j_decompress_ptr cinfo,
                 vector<JOCTET>& icc_data_out)
{
    icc_data_out.clear();                                       // avoid confusion if false return

    vector<bool> marker_present(MAX_SEQ_NO+1);             // TRUE if marker found
    vector<unsigned int> data_length(MAX_SEQ_NO+1);        // size of profile data in marker

    // This first pass over the saved markers discovers whether there are
    // any ICC markers and verifies the consistency of the marker numbering.

    // 1. reset content of the vector marker_present
    fill(marker_present.begin(), marker_present.end(), false);

    // 2. go thru marker's list and check every node
    int num_markers = 0;
    for (jpeg_saved_marker_ptr marker = cinfo->marker_list;
         marker != NULL;
         marker = marker->next)
    {
        if (marker_is_icc(marker))
        {
            if (num_markers == 0)
            {
                num_markers = GETJOCTET(marker->data[13]);
            }
            else if (num_markers != GETJOCTET(marker->data[13]))
            {
                // inconsistent num_markers fields
                return false;
            }
            int seq_no = GETJOCTET(marker->data[12]);
            if (seq_no <= 0 || seq_no > num_markers)
            {
                // bogus sequence number
                return false;
            }
            if (marker_present[seq_no])
            {
                // duplicate sequence numbers
                return false;
            }
            marker_present[seq_no] = true;
            data_length[seq_no] = marker->data_length - ICC_OVERHEAD_LEN;
        }
    }

    if (num_markers == 0)
    {
        return false;
    }

    // Check for missing markers, count total space needed,
    // compute offset of each marker's part of the data.
    std::vector<unsigned int> data_offset(MAX_SEQ_NO+1);        // offset for data in marker
    unsigned int total_length = 0;
    for (int seq_no = 1; seq_no <= num_markers; seq_no++)
    {
        if (marker_present[seq_no] == 0)
        {
            // missing sequence number
            return false;
        }
        data_offset[seq_no] = total_length;
        total_length += data_length[seq_no];
    }

    if (total_length <= 0)
    {
        return false;		// found only empty markers?
    }

    // Allocate space for assembled data
    std::vector<JOCTET> icc_data(total_length);   // JOCTET *icc_data;
    //  and fill it in
    for (jpeg_saved_marker_ptr marker = cinfo->marker_list;
         marker != NULL;
         marker = marker->next)
    {
        if (marker_is_icc(marker))
        {
            int seq_no              = GETJOCTET(marker->data[12]);
            unsigned int length     = data_length[seq_no];

            JOCTET *dst         = icc_data.data() + data_offset[seq_no];
            JOCTET FAR *src     = marker->data + ICC_OVERHEAD_LEN;

            copy(src, src + length, dst);
        }
    }

    icc_data_out.swap(icc_data);

    return true;
}
//
//
// End of code from iccjpeg.c
//
///////////////////////////////////////////////////////////////////////////////

}

class JpegReaderImpl
{
public:
    JpegReaderImpl(JpegReader* jpeg_reader):
        jpeg_reader_(jpeg_reader)
    {}

    void open(const std::string& filename)
    {
        file_.reset(fopen(filename.c_str(), "rb"));
        if ( file_.get() == NULL )
        {
            filename_.clear();
            throw OpenException("JPEG: Cannot open " + filename);
        }
        filename_ = filename;
    }

    void close()
    {
        file_.reset();
        filename_.clear();
    }

    ImagePtr readFrame(const Settings& settings)
    {
        LIBHDR_POSSIBLY_UNUSED(settings);

        if ( isOpen() == false ) throw NotOpenException("JPEG: no file open!");

        jpeg_decompress_struct cinfo;
        jpeg_error_mgr error_ctrl;

        cinfo.err = jpeg_std_error(&error_ctrl);
        error_ctrl.error_exit      = error_handler;
        error_ctrl.output_message  = output_message;

        jpeg_create_decompress(&cinfo);         // Created decompressor
        jpeg_stdio_src(&cinfo, file_.get());    // Assigned input source

        setup_read_icc_profile(&cinfo);         // Init CMS
        jpeg_read_header(&cinfo, true);         // Read JPEG headers

        // start progress notification
        jpeg_reader_->notifyStart();

        ResourceHandler<void, DeleterCmsTransform> xform;
        bool do_cms = false;
        {
            std::vector<JOCTET> temp_buffer;

            ResourceHandler<void, DeleterCmsProfile> h_srgb;
            ResourceHandler<void, DeleterCmsProfile> h_in;

            if ( read_icc_profile(&cinfo, temp_buffer) )
            {
                h_srgb.reset( cmsCreate_sRGBProfile() );
                h_in.reset( cmsOpenProfileFromMem(temp_buffer.data(), temp_buffer.size()) );

                if ( h_in.get() != NULL )
                {
                    switch (cmsGetColorSpace(h_in.get()))
                    {
                    case cmsSigRgbData:
                        xform.reset(cmsCreateTransform(h_in.get(), TYPE_RGB_8,
                                                   h_srgb.get(), TYPE_RGB_8,
                                                   INTENT_PERCEPTUAL, 0));
                        break;
//                    case cmsSigCmykData:
//                        xform = cmsCreateTransform(h_in, TYPE_CMYK_8,
//                                                  h_srgb, TYPE_RGBA_8,
//                                                   INTENT_PERCEPTUAL, 0);
//                        break;
                    default:
                        throw ReadException("JPEG: unsupported input colorspace!");
                        break;
                    }

                    if (xform.get() != NULL)
                        do_cms = true;
                }
            }
        }

        jpeg_start_decompress(&cinfo); // Start decompress

        ImagePtr image(new Image(cinfo.output_width, cinfo.output_height));

        // output
        Pixel* pixels = image->data();
        // input - if an exception is raised, this buffer gets deleted correctly
        vector<JSAMPLE> scanline(cinfo.num_components*cinfo.output_width);
        JSAMPROW scanline_buffer[1] = { scanline.data() };   // it's a bit of a cheat, but it works :)

        // notify job length
        jpeg_reader_->notifyJobLength(cinfo.output_height);
        while (cinfo.output_scanline < cinfo.output_height)
        {
            jpeg_read_scanlines(&cinfo, scanline_buffer, 1);

            if (do_cms)
                cmsDoTransform(xform.get(), scanline.data(), scanline.data(), cinfo.output_width);

            fill_image(pixels, scanline.data(), cinfo.output_width, cinfo.num_components);

            pixels += cinfo.output_width;
            jpeg_reader_->notifyJobNextStep();
        }
        jpeg_reader_->notifyStop();

        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);

        // read EXIF DATA!
        image->exifData().fromFile(filename_);

        return image;
    }

    bool isOpen()
    {
        return (file_.get() != NULL);
    }

private:
    ResourceHandler<FILE> file_;
    JpegReader* jpeg_reader_;
    std::string filename_;
};

JpegReader::JpegReader()
{
    impl_.reset(new JpegReaderImpl(this));
}

JpegReader::~JpegReader()
{}

void JpegReader::open(const std::string& filename)
{
    impl_->open(filename);
}

ImagePtr JpegReader::readFrame(const Settings& settings)
{
    return impl_->readFrame(settings);
}

void JpegReader::close()
{
    impl_->close();
}

bool JpegReader::isOpen()
{
    return ( impl_->isOpen() );
}

std::vector<std::string> JpegReader::getID()
{
    std::vector<std::string> id;

    id.push_back("jpg");
    id.push_back("jpeg");

    return id;
}

REGISTER_FRAMEREADER(JpegReader)

} // namespace IO
} // namespace LibHDR

