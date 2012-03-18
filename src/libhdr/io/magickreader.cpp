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

#include "libhdr/io/magickreader.h"
#include "libhdr/io/framereader.aux.h"
#include "libhdr/io/ioexceptions.h"
#include "libhdr/image.h"

#include <iostream>
#include <string>
#include <Magick++.h>

namespace LibHDR
{
namespace IO
{
using namespace std;

namespace
{
const float DIVQUANTUMRANGE = 1.0f/static_cast<float>(QuantumRange);

inline void to8Bit(const Magick::Color& in_color, LibHDR::Pixel& out_pixel)
{
    out_pixel.f32[0] = static_cast<float>(in_color.redQuantum())*DIVQUANTUMRANGE;
    out_pixel.f32[1] = static_cast<float>(in_color.greenQuantum())*DIVQUANTUMRANGE;
    out_pixel.f32[2] = static_cast<float>(in_color.blueQuantum())*DIVQUANTUMRANGE;
    out_pixel.f32[3] = 1.0f;
}
}

class MagickReaderImpl
{
public:
    MagickReaderImpl(MagickReader* magickReader):
        m_MagickReader(magickReader)
    {}

    void open(const std::string& filename)
    {
        try
        {
            // If already open, it will get rid of the old one and open the new one
            m_MagickImage.reset( new Magick::Image(filename) );
        } catch (...)
        {
            throw OpenException("Magick++: could not initialise a Magick::Image object");
        }
    }

    void close()
    {
        m_MagickImage.reset();
    }

    ImagePtr readFrame(const Settings& /*settings*/)
    {
        // They must be a way to have an implementation of this function that runs faster...

        if ( !this->isOpen() ) throw NotOpenException("Magick++: file not open");

        m_MagickReader->notifyStart();

        ImagePtr image(new Image(m_MagickImage->columns(), m_MagickImage->rows()));

        Pixel* pixels = image->data();

        m_MagickReader->notifyJobLength(m_MagickImage->rows());

        for (size_t r = 0; r < m_MagickImage->rows(); ++r)
        {
            for (size_t c = 0; c < m_MagickImage->columns(); ++c)
            {
                to8Bit( m_MagickImage->pixelColor(c, r), *pixels );

                pixels++;
            }

            m_MagickReader->notifyJobNextStep();
        }

        image->setBitPerSample(Frame::BPS_8);
        image->setImageType(Image::RGB);
        image->setSampleType(Frame::UINT);

        m_MagickReader->notifyStop();

        return image;
    }

    bool isOpen()
    {
        return ( m_MagickImage.get() );
    }

private:
    boost::shared_ptr<Magick::Image> m_MagickImage;
    MagickReader* m_MagickReader;
};

MagickReader::MagickReader()
{
    m_MagickReaderImpl.reset(new MagickReaderImpl(this));
}

MagickReader::~MagickReader()
{}

void MagickReader::open(const std::string& filename)
{
    m_MagickReaderImpl->open(filename);
}

ImagePtr MagickReader::readFrame(const Settings& settings)
{
    return m_MagickReaderImpl->readFrame(settings);
}

void MagickReader::close()
{
    m_MagickReaderImpl->close();
}

bool MagickReader::isOpen()
{
    return ( m_MagickReaderImpl->isOpen() );
}

std::vector<std::string> MagickReader::getID()
{
    std::vector<std::string> id;

    id.push_back("jpg");
    id.push_back("jpeg");

    return id;
}

REGISTER_FRAMEREADER(MagickReader)

} // namespace IO
} // namespace LibHDR

