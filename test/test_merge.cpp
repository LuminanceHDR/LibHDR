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
 *
 */

//! \file test_merge.cpp
//! \brief test merge functionalities

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <libhdr/merge/debevec97.h>
#include <libhdr/io/magickreader.h>
#include <libhdr/io/tiffwriter.h>
#include <libhdr/io/exrwriter.h>
//#include <libhdr/io/framereader.h>
//#include <libhdr/io/framewriter.h>

#include "mockcallback.h"

using namespace LibHDR;
using namespace std;

namespace
{
class NormalizerAndGamma
{
public:
    NormalizerAndGamma(float min, float max, float gamma):
        min_(min),
        max_(max),
        diff_(max - min),
        gamma_(1.f/gamma)
    {}

    void operator()(Pixel& pixel)
    {
        // normalize red
        pixel.f32[0] = powf((pixel.f32[0] - min_)/diff_, gamma_);
        pixel.f32[1] = powf((pixel.f32[1] - min_)/diff_, gamma_);
        pixel.f32[2] = powf((pixel.f32[2] - min_)/diff_, gamma_);
        pixel.f32[3] = 1.0f;
    }

    float min_;
    float max_;
    float diff_;
    float gamma_;
};

void normalize(Pixel* pixels, size_t num_pixels, float gamma)
{
    const float* data = reinterpret_cast<const float*>(pixels);

    float min = *std::min_element(data, data+(num_pixels << 2));
    float max = *std::max_element(data, data+(num_pixels << 2));

    std::cout << "Min/Max: " << min << ", " << max << std::endl;

    for_each(pixels, pixels+num_pixels, NormalizerAndGamma(min, max, gamma));
}
}

int main(int argc, char** argv)
{
    if ( argc < 2 )
    {
        cerr << "No enough parameters" << endl;
        cerr << "Usage: " << argv[0] << " <input files> <output file>" << endl;

        return -1;
    }

    // create merge based on Debevec97
    Merge::Debevec97 debevec;

    LibHDRTest::MockCallback cb;
    try
    {
        //create TIFF Writer
        //boost::shared_ptr< IO::FrameWriter > writer( IO::FrameWriterFactory::instance().create("tif") );
        boost::shared_ptr< IO::FrameWriter > writer( new IO::TIFFWriter );
        boost::shared_ptr< IO::FrameWriter > writer_exr( new IO::EXRWriter );

        // create JPG Reader
        //boost::shared_ptr< IO::FrameReader > reader( IO::FrameReaderFactory::instance().create("jpg") );
        boost::shared_ptr< IO::FrameReader > reader( new IO::MagickReader );


        std::vector<ImagePtr> images;
        for (int idx = 1; idx < (argc-1); ++idx)
        {
            reader->open(argv[idx]);
            images.push_back( reader->readFrame() );
            reader->close();

            cout << images[images.size() - 1]->exifData() << endl;
        }

        ImagePtr hdr_image( debevec.merge(images) );

        writer_exr->subscribe(&cb);

        writer_exr->open("test.exr");
        writer_exr->writeFrame( hdr_image );
        writer_exr->close();

        normalize(hdr_image->data(), hdr_image->getElems(), 2.2f);

        writer->open( argv[argc-1] );
        writer->writeFrame( hdr_image );
        writer->close();

        return 0;
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}
