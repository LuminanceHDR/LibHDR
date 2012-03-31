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

#include "exrwriter.h"

#include <string>
#include <algorithm>
#include <ImfRgbaFile.h>
#include <ImfArray.h>
#include <boost/scoped_array.hpp>
#include <libhdr/image.h>

namespace LibHDR
{
namespace IO
{
struct EXRWriterImpl
{
    std::string m_filename;
};

EXRWriter::EXRWriter():
    m_EXRWriterImpl(new EXRWriterImpl)
{}

EXRWriter::~EXRWriter()
{}

void EXRWriter::open(const std::string& filename)
{
    // just stores the name of the file inside the internal structure
    m_EXRWriterImpl->m_filename = filename;
}

namespace
{
// converts LibHDR::Pixel to Imf::Rgba
inline Imf::Rgba Pixel2Rgba(const LibHDR::Pixel& pixel)
{
    return Imf::Rgba(pixel.f32[0],
                     pixel.f32[1],
                     pixel.f32[2]);
}
}


bool EXRWriter::writeFrame(const ImagePtr frame, const Settings& /*settings*/)
{
    using std::transform;

    try
    {
        // calculate maximum
        const int width = frame->getWidth();
        const int height = frame->getHeight();

        this->notifyStart();
        //this->notifyJobLength(height);

        Imf::RgbaOutputFile file(m_EXRWriterImpl->m_filename.c_str(), width, height, Imf::WRITE_RGBA);

        boost::scoped_array<Imf::Rgba> pixel_buffer(new Imf::Rgba[width*height]);

        const Pixel* pixels = frame->constData();

        //for (int row = 0; row < height; ++row)
        //{
            // convert a row of pixels
            transform(pixels, pixels+width*height, pixel_buffer.get(), Pixel2Rgba);

            file.setFrameBuffer(pixel_buffer.get(), 1, width);
            file.writePixels(height); // 1 row!

            // next row!
        //    pixels += width;
        //    this->notifyJobNextStep();
        //}
        this->notifyStop();
        return true;
    }
    catch (const std::exception& e)
    {
        throw WriteException(std::string("EXR: could not write strip")+e.what());
    }
}

void EXRWriter::close()
{
    m_EXRWriterImpl->m_filename.clear();
}

bool EXRWriter::isOpen()
{
    return !m_EXRWriterImpl->m_filename.empty();
}

}
}
