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

#include "libhdr/io/tiffwriter.h"
#include "libhdr/io/framewriter.aux.h"
#include "libhdr/image.h"

#include <tiffio.h>
#include <algorithm>
#include <cassert>
#include <boost/cstdint.hpp>

namespace LibHDR
{
namespace IO
{
using namespace std;

namespace
{
const uint16_t ALPHA_ASSOC[1] = { EXTRASAMPLE_ASSOCALPHA };
}

class TIFFWriterImpl
{
public:
    TIFFWriterImpl(TIFFWriter* tiff_writer):
        m_TIFFWriter(tiff_writer),
        m_TIFF(NULL)
    {}

    ~TIFFWriterImpl()
    {
        close();
    }

    void open(const std::string& filename)
    {
        if ( m_TIFF != NULL )
        {
            TIFFClose(m_TIFF);
        }
        m_TIFF = TIFFOpen(filename.c_str(), "w");
        if ( !m_TIFF )
        {
            throw OpenException("TIFF: could not open file for writing");
        }
    }

    void close()
    {
        if ( m_TIFF != NULL )
        {
            TIFFClose(m_TIFF);
            m_TIFF = NULL;

            assert(m_TIFF == NULL);
        }
    }

    bool isOpen()
    {
        return (m_TIFF != NULL);
    }

    void write8BitTiff(const Image& frame, const Settings& /*settings*/)
    {
        if ( m_TIFF == NULL ) throw NotOpenException("TIFF: file not open");

        // Generic TIFF properties
        TIFFSetField (m_TIFF, TIFFTAG_IMAGEWIDTH, frame.getWidth());
        TIFFSetField (m_TIFF, TIFFTAG_IMAGELENGTH, frame.getHeight());
        TIFFSetField (m_TIFF, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField (m_TIFF, TIFFTAG_EXTRASAMPLES, 1, &ALPHA_ASSOC);
        TIFFSetField (m_TIFF, TIFFTAG_SAMPLESPERPIXEL, 4);
        TIFFSetField (m_TIFF, TIFFTAG_ROWSPERSTRIP, 1);

        // 8 bit specific properties
        TIFFSetField (m_TIFF, TIFFTAG_COMPRESSION, COMPRESSION_DEFLATE);
        TIFFSetField (m_TIFF, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
        TIFFSetField (m_TIFF, TIFFTAG_BITSPERSAMPLE, 8);

        // data allocation
        const tsize_t strip_size = TIFFStripSize(m_TIFF);
        const tstrip_t number_of_strips = TIFFNumberOfStrips(m_TIFF);

        //std::cout << "Strip size: " << strip_size << "\n";
        //std::cout << "Strip number: " << number_of_strips << "\n";

        boost::shared_ptr<uint32_t> strip_buffer( (uint32_t*)_TIFFmalloc(strip_size) , &_TIFFfree );

        if ( !strip_buffer )
        {
            throw WriteException("TIFF: error allocating buffer");
        }
        // I have enough space for a strip
        // so I create nice pointers to my data
        uint32_t* strip_buf = boost::get_pointer( strip_buffer );
        const Pixel* frame_data = frame.constData();
        const int WIDTH = frame.getWidth();

        // Notify length and start
        m_TIFFWriter->notifyJobLength(number_of_strips);
        m_TIFFWriter->notifyStart();

        for (tstrip_t strip = 0; strip < number_of_strips; ++strip)
        {
            // Transform a row of Pixel(s) to uint32_t(s) (every uint32_t contains 4 uint8_t)
            copy(frame_data,                   // from (start)
                 frame_data + WIDTH,           // from (stop)
                 strip_buf                     // to
                 );           // automatic conversion from Pixel to uint32_t

            // update pointer to frame_data
            frame_data += WIDTH;

            // Write strip into final file
            tsize_t written = TIFFWriteEncodedStrip(m_TIFF, strip, strip_buf, strip_size);
            if ( written == -1 || written != strip_size )
            {
                // I have encountered an error, so I have to stop the current
                // calculation and raise an exception
                m_TIFFWriter->notifyStop();

                throw WriteException("TIFF: error writing data strip");
            }

            m_TIFFWriter->notifyJobNextStep();
        }
        m_TIFFWriter->notifyStop();

        // No need of a explicit call to the free function, thanks to boost::shared_ptr
        //_TIFFfree(strip_buf);
    }

private:
    TIFFWriter* m_TIFFWriter;
    TIFF* m_TIFF;
};

TIFFWriter::TIFFWriter()
{
    m_TIFFWriterImpl.reset( new TIFFWriterImpl(this) );
}

TIFFWriter::~TIFFWriter()
// I don't need to call "close()", because the Pimpl's destructor will do that
{}

void TIFFWriter::open(const std::string& filename)
{
    m_TIFFWriterImpl->open(filename);
}

bool TIFFWriter::writeFrame(const ImagePtr frame, const Settings& settings)
{
    m_TIFFWriterImpl->write8BitTiff(*frame, settings);
    return true;
}

void TIFFWriter::close()
{
    m_TIFFWriterImpl->close();
}

bool TIFFWriter::isOpen()
{
    return m_TIFFWriterImpl->isOpen();
}

vector<string> TIFFWriter::getID()
{
    vector<string> id;

    id.push_back("tif");
    id.push_back("tiff");

    return id;
}

REGISTER_FRAMEWRITER(TIFFWriter)

} // namespace LibHDR
} // namespace IO
