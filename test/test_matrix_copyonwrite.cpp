/*
 * This file is a part of LibHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2011 Davide Anastasia
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 */

#include <iostream>
#include <sstream>
#include <list>
#include <new>

#include <libhdr/frame.h>

#include "test_utils.h"

namespace
{

const int WIDTH = 3000;
const int HEIGHT = 2000;

const float* test_function1(LibHDR::Frame frame)
{
    return frame.constData();
}

}

int main(int argc, char *argv[])
{
    if ( !check_parameters(argc, argv) )
        return 1;

    switch (get_mode(argv[1]))
    {
    case 1:
    {
        // test copy-on-write
        std::cout << "Test copy-on-write: should not copy the underlying data" << std::endl;

        LibHDR::Frame frame(WIDTH, HEIGHT);

        const float* data = frame.constData();

        LibHDR::Frame frame2 = frame;
        const float* data2 = frame2.constData();

        std::stringstream ss;
        ss << "(data = ";
        ss << data;
        ss << ", data2 = ";
        ss << data2;
        ss << ")";

        if ( data == data2 )
        {
            std::cout << "Ok " << ss.str() << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Failed " << ss.str() << std::endl;
            return 1;
        }
    }
        break;
    case 2:
    {
        // test copy-on-write
        std::cout << "Test copy-on-write: should COPY the underlying data" << std::endl;

        LibHDR::Frame frame(WIDTH, HEIGHT);

        const float* data = frame.constData();

        LibHDR::Frame frame2 = frame;

        frame2(0) = LibHDR::Pixel();    // should make a copy here!

        const float* data2 = frame2.constData();

        std::stringstream ss;
        ss << "(data = ";
        ss << data;
        ss << ", data2 = ";
        ss << data2;
        ss << ")";

        if ( data != data2 )
        {
            std::cout << "Ok " << ss.str() << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Failed " << ss.str() << std::endl;
            return 1;
        }
    }
        break;

    case 3:
    {
        // test copy-on-write
        std::cout << "Test copy-on-write: function argument (should not copy the underlying data)" << std::endl;

        LibHDR::Frame frame(WIDTH, HEIGHT);

        const float* data = frame.constData();

        const float* data2 = test_function1(frame);

        std::stringstream ss;
        ss << "(data = ";
        ss << data;
        ss << ", data2 = ";
        ss << data2;
        ss << ")";

        if ( data == data2 )
        {
            std::cout << "Ok " << ss.str() << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Failed " << ss.str() << std::endl;
            return 1;
        }
    }
        break;
    case 4:
    {
        try {
            // test copy-on-write
            std::cout << "Test copy-on-write: allocation of 10 frames of 6mpix (3000x2000)" << std::endl;
            std::cout << "This test should be used to check for memory leaks with any profiling tool "
                << "and to measure the speed of the deep copy" << std::endl;

            bool test = true;

            std::list<LibHDR::Frame> list_of_frames;

            LibHDR::Frame frame(3000, 2000);
            const float* dt = frame.constData();

            for (int idx = 0; idx < 10; idx++)
            {
                std::list<LibHDR::Frame>::iterator it = list_of_frames.insert(list_of_frames.end(), frame);
                float* data = (*it).data(); // this line forces the code to make a deep copy

                if ( dt == data ) test = false; // it must NOT be the same, because of the deep copy
            }

            if ( test )
            {
                std::cout << "Ok" << std::endl;
                return 0;
            }
            else
            {
                std::cout << "Failed" << std::endl;
                return 1;
            }

            std::cout << "Ok " << std::endl;
            return 0;

        } catch ( std::bad_alloc& ba )
        {
            std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
            return 1;
        }
    }
        break;

    default:
        std::cout << "funziona";
        return 0;
    }
}
