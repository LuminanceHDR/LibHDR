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

#include "libhdr/io/framewriter.h"
#include "libhdr/io/framereader.h"
#include "libhdr/image.h"
#include "mockcallback.h"

#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <iostream>

using namespace LibHDR;
using namespace std;

const int WIDTH = 40;
const int HEIGTH = 30;

int main(int /*argc*/, char** /*argv*/)
{
    // create empty frame, with red Pixel(s)
    ImagePtr frame( new Image(WIDTH, HEIGTH));
    Pixel* fdata = reinterpret_cast<Pixel*>(frame->data());
    for (int idx = 0; idx < WIDTH*HEIGTH; ++idx)
    {
        fdata[idx] = Pixel(1.f, 0.f, 0.f, 1.f);  // R G B
    }

    // Callback!
    LibHDRTest::MockCallback cb;
    try
    {
        // create TIFF Writer
        boost::shared_ptr< IO::FrameWriter > writer( IO::FrameWriterFactory::instance().create("tif") );
        boost::shared_ptr< IO::FrameReader > reader( IO::FrameReaderFactory::instance().create("tif") );

        writer->subscribe(&cb);
        reader->subscribe(&cb);

        writer->open("test.tif");
        writer->writeFrame( frame );
        writer->close();

        reader->open("test.tif");
        boost::shared_ptr<Image> read_frame( reader->readFrame(Settings()) );
        reader->close();

        LibHDR::Pixel* pre = frame->data();
        LibHDR::Pixel* post = read_frame->data();

        int cmp = memcmp((void*)(post), (void*)(pre), sizeof(float)*WIDTH*HEIGTH);

        if (cmp)
        {
            for (unsigned int idx = 0; idx < sizeof(float)*WIDTH*HEIGTH; ++idx)
            {
                if ( pre[idx] != post[idx] )
                    std::cout << idx << ", ref = " << pre[idx] << ", Post = " << post[idx] << std::endl;
            }
            cout << cmp << endl;
        }
        return cmp;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

}
