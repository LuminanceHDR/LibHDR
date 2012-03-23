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

int main(int argc, char** argv)
{
    std::string in_file;
    std::string out_file;
    if (argc >= 3)
    {
        in_file = argv[1];
        out_file = argv[2];
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return -1;
    }

    LibHDRTest::MockCallback cb;
    try
    {
        // create TIFF Writer
        boost::shared_ptr< IO::FrameWriter > writer( IO::FrameWriterFactory::instance().create("tif") );
        // create JPG Reader
        boost::shared_ptr< IO::FrameReader > reader( IO::FrameReaderFactory::instance().create("jpg") );

        // Subscribe
        writer->subscribe(&cb);
        reader->subscribe(&cb);

        reader->open(in_file);
        ImagePtr read_frame( reader->readFrame(Settings()) );
        reader->close();

        cout << read_frame->exifData() << endl;

        writer->open(out_file);
        writer->writeFrame( read_frame );
        writer->close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

}
