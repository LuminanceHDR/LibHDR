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
#include "libhdr/frame.h"

#include <tiffio.h>
#include <boost/cstdint.hpp>

namespace LibHDR
{
namespace IO
{
namespace
{

inline uint8_t convertFloatTo8Bit(const float& fl)
{
    return static_cast<uint8_t>((fl*255.f) + 0.5f);
    //std::cout << (int)v << " " << std::endl;
}
}


class TIFFWriterImpl
{
public:
    TIFFWriterImpl(TIFFWriter& tiff_writer):
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
            m_TIFF == NULL;
        }
    }

    bool isOpen()
    {
        return (m_TIFF != NULL);
    }

    void write8BitTiff(const Frame& frame, const Settings& /*settings*/)
    {
        // Generic TIFF properties
        TIFFSetField (m_TIFF, TIFFTAG_IMAGEWIDTH, frame.getWidth());
        TIFFSetField (m_TIFF, TIFFTAG_IMAGELENGTH, frame.getHeight());
        TIFFSetField (m_TIFF, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        //TIFFSetField (m_TIFF, TIFFTAG_EXTRASAMPLES, EXTRASAMPLE_ASSOCALPHA);
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

        boost::shared_ptr<uint8_t> strip_buffer( (uint8_t*)_TIFFmalloc(strip_size) , &_TIFFfree);

        if ( !strip_buffer )
        {
            throw WriteException("TIFF: error allocating buffer");
        }
        // I have enough space for a strip
        // so I create nice pointers to my data ready
        uint8_t* strip_buf = strip_buffer.get();
        const float* frame_data = frame.constData();
        const int WIDTH = frame.getWidth();

        // Notify length and start
        m_TIFFWriter.notifyJobLength( number_of_strips );
        m_TIFFWriter.notifyStart();

        for (tstrip_t strip = 0; strip < number_of_strips; ++strip)
        {
            for (tsize_t col = 0; col < WIDTH; ++col)
            {
                // red
                strip_buf[4*col] = convertFloatTo8Bit(frame_data[4*col]);
                // green
                strip_buf[4*col+1] = convertFloatTo8Bit(frame_data[4*col+1]);
                // blue
                strip_buf[4*col+2] = convertFloatTo8Bit(frame_data[4*col+2]);
                // alpha
                //strip_buf[4*col+3] = convertFloatTo8Bit(frame_data[4*col+3]);
                strip_buf[4*col+3] = 255;
            }
            // Update location pointer
            frame_data += WIDTH*4;
            
            // Write strip into final file
            tsize_t written = TIFFWriteEncodedStrip(m_TIFF, strip, strip_buf, strip_size);
            if ( written == -1 || written != strip_size )
            {
                throw WriteException("TIFF: error writing data strip");
            }
            else
            {
                m_TIFFWriter.notifyJobNextStep();
            }
        }
        m_TIFFWriter.notifyStop();
        // No need of a explicit call to the free function, thanks to boost::shared_ptr
        //_TIFFfree(strip_buf);
    }

private:
    TIFFWriter& m_TIFFWriter;

    TIFF* m_TIFF;
};

TIFFWriter::TIFFWriter()
{
    m_TIFFWriterImpl.reset( new TIFFWriterImpl(*this) );
}

TIFFWriter::~TIFFWriter()
// I don't need to call "close()", because the Pimpl's destructor will do that
{}

void TIFFWriter::open(const std::string& filename)
{
    m_TIFFWriterImpl->open(filename);
}

bool TIFFWriter::writeFrame(const Frame& frame, const Settings& settings)
{
    m_TIFFWriterImpl->write8BitTiff(frame, settings);
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

std::vector<std::string> TIFFWriter::getID()
{
    std::vector<std::string> id;

    id.push_back("tif");
    id.push_back("tiff");

    return id;
}

REGISTER_FRAMEWRITER(TIFFWriter)

}
}
