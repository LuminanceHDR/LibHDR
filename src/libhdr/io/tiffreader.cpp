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

#include "libhdr/io/tiffreader.h"
#include "libhdr/io/framereader.aux.h"
#include "libhdr/image.h"

#include <tiffio.h>
#include <algorithm>
#include <cassert>
#include <memory>
#include <boost/cstdint.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/tr1/memory.hpp>

namespace LibHDR
{
namespace IO
{
using namespace std;

namespace
{
const float DIV255 = 1.0f/255.f;
}

struct TIFFReaderParameters
{
    uint32_t width;
    uint32_t height;

    uint16_t photometric_type;
    uint16_t bit_per_sample;
    uint16_t samples_per_pixel;

    bool     has_alpha;
};
    /*
  uint32 width, height;

  uint16 comp;                  /// compression type
  uint16 phot;                  /// type of photometric data
  enum {FLOATLOGLUV, FLOAT, WORD, BYTE} TypeOfData; //FLOAT is the wasting space one, FLOATLOGLUV is Greg Ward's format
  uint16 bps;                   /// bits per sample
  uint16 nSamples;              /// number of channels in tiff file (only 1-3 are used)
  bool has_alpha;
  double stonits;               /// scale factor to get nit values
  */
//  };

class TIFFReaderImpl
{
public:
    TIFFReaderImpl(TIFFReader* tiff_reader):
        m_TIFFReader(tiff_reader),
        m_TIFF(NULL)
    {}

    ~TIFFReaderImpl()
    {
        close();
    }

    void open(const std::string& filename)
    {
        if ( m_TIFF != NULL )
        {
            TIFFClose(m_TIFF);
        }
        m_TIFF = TIFFOpen(filename.c_str(), "r");
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

    void readLogLuv(Image* /*frame*/, const TIFFReaderParameters& /*parameters*/)
    {
//        // compression type
//        uint16_t compression_type;
//        if ( !TIFFGetField(m_TIFF, TIFFTAG_COMPRESSION, &compression_type) )
//        {
//            compression_type = COMPRESSION_NONE;
//        }

//        if ( (compression_type != COMPRESSION_SGILOG) && (compression_type != COMPRESSION_SGILOG24) )
//        {
//            throw ReadException("TIFF: only support SGILOG compressed LogLuv data");
//        }
//        TIFFSetField(m_TIFF, TIFFTAG_SGILOGDATAFMT, SGILOGDATAFMT_FLOAT);
    }

    inline void read8BitInt(Image* frame, const TIFFReaderParameters& parameters)
    {
        tdata_t buffer =  _TIFFmalloc( TIFFScanlineSize(m_TIFF) );

        float* pixels = reinterpret_cast<float*>(frame->data());

        m_TIFFReader->notifyJobLength(parameters.height);
        m_TIFFReader->notifyStart();

        for (uint32_t row = 0; row < parameters.height; ++row)
        {
            TIFFReadScanline(m_TIFF, buffer, row);

            uint8_t* inner_loop_buffer = static_cast<uint8_t*>(buffer);
            for (uint32_t sample = 0; sample < parameters.width; ++sample)
            {
                pixels[0] = inner_loop_buffer[0]*DIV255; //powf(inner_loop_buffer[0]*DIV255, 2.2f);      // red
                pixels[1] = inner_loop_buffer[1]*DIV255; //powf(inner_loop_buffer[1]*DIV255, 2.2f);      // green
                pixels[2] = inner_loop_buffer[2]*DIV255; //powf(inner_loop_buffer[2]*DIV255, 2.2f);      // blue
                pixels[3] = 1.0f;                                         // alpha

                pixels += 4;
                inner_loop_buffer += parameters.samples_per_pixel;
            }
            m_TIFFReader->notifyJobNextStep();
        }

        m_TIFFReader->notifyStop();

        frame->setBitPerSample(Frame::BPS_8);
        frame->setImageType(Image::RGB);
        frame->setSampleType(Frame::UINT);
    }

    void read16BitInt(Image* /*frame*/, const TIFFReaderParameters& /*parameters*/)
    {

    }
    void read32BitFloat(Image* /*frame*/, const TIFFReaderParameters& /*parameters*/)
    {

    }

    ImagePtr readFrame(const Settings& /*settings*/)
    {
        if (m_TIFF == NULL) throw NotOpenException("TIFF: file not open");

        TIFFReaderParameters parameters;

        TIFFGetField(m_TIFF, TIFFTAG_IMAGEWIDTH, &parameters.width);
        TIFFGetField(m_TIFF, TIFFTAG_IMAGELENGTH, &parameters.height);

        if ( !parameters.width || !parameters.height )
        {
            throw ReadException("TIFF: Invalid image size");
        }

        ImagePtr image(new Image(parameters.width, parameters.height));

//        if (!TIFFGetField(tif, TIFFTAG_STONITS, &parameters.stonits))
//        {
//            parameters.stonits = 1.;
//        }

        // type of photometric data
        if ( !TIFFGetFieldDefaulted(m_TIFF, TIFFTAG_PHOTOMETRIC, &parameters.photometric_type) )
        {
            throw ReadException("TIFF: unspecified photometric type");
        }

        uint16_t* extra_sample_types = 0;
        uint16_t  extra_samples_per_pixel = 0;

        if (TIFFGetField(m_TIFF, TIFFTAG_EXTRASAMPLES, &extra_samples_per_pixel, &extra_sample_types ) != 1)
        {
            extra_samples_per_pixel = 0;
        }

        TIFFGetField(m_TIFF, TIFFTAG_SAMPLESPERPIXEL, &parameters.samples_per_pixel); // should never fail!

        uint16_t samples_per_pixel = parameters.samples_per_pixel - extra_samples_per_pixel;
        parameters.has_alpha = (extra_samples_per_pixel == 1);

        if ( samples_per_pixel != 3 )
        {
            throw ReadException("TIFF: unsupported samples per pixel for RGB");
        }

        switch (parameters.photometric_type)
        {
        case PHOTOMETRIC_LOGLUV:
        {
            // Read DATA!
            readLogLuv(image.get(), parameters);
            break;
        }
        case PHOTOMETRIC_RGB:
        {
            if ( !TIFFGetField(m_TIFF, TIFFTAG_BITSPERSAMPLE, &parameters.bit_per_sample) )
            {
                throw ReadException("TIFF: unsupported bits per sample for RGB");
            }

            switch (parameters.bit_per_sample)
            {
            case 8:
            {
                // Read 8 bit per sample!
                read8BitInt(image.get(), parameters);
                break;
            }
            case 16:
            {
                // Read 16 bit per sample!
                read16BitInt(image.get(), parameters);
                break;
            }
            case 32:
            {
                // Read 32 bit per sample!
                read32BitFloat(image.get(), parameters);
                break;
            }
            default:
            {
                throw ReadException("TIFF: unsupported bits per sample for RGB");
                break;
            }
            }
            break;
        }
        default:
        {
            throw ReadException("TIFF: unsupported photometric type");
            break;
        }
        }
        return image;
    }

private:
    TIFFReader* m_TIFFReader;
    TIFF* m_TIFF;
};

TIFFReader::TIFFReader()
{
    m_TIFFReaderImpl.reset( new TIFFReaderImpl(this) );
}

TIFFReader::~TIFFReader()
// I don't need to call "close()", because the Pimpl's destructor will do that
{}

void TIFFReader::open(const std::string& filename)
{
    m_TIFFReaderImpl->open(filename);
}

void TIFFReader::close()
{
    m_TIFFReaderImpl->close();
}

ImagePtr TIFFReader::readFrame(const Settings& settings)
{
    return m_TIFFReaderImpl->readFrame(settings);
}

bool TIFFReader::isOpen()
{
    return m_TIFFReaderImpl->isOpen();
}

std::vector<std::string> TIFFReader::getID()
{
    vector<string> id;

    id.push_back("tif");
    id.push_back("tiff");

    return id;
}

REGISTER_FRAMEREADER(TIFFReader)

} // namespace IO
} // namespace LibHDR

