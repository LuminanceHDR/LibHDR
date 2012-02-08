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

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "libhdr_version.h"
#include "libhdr/io/framereader.h"
#include "libhdr/io/framewriter.h"

using namespace std;
using namespace LibHDR;

typedef vector<string> VecOfString;

int main(int argc, char *argv[])
{
    cout << "LibHDR V." << Version::getVersion() << "\n";

    VecOfString input_types = IO::FrameReaderFactory::instance().getSubscribed();
    cout << "Input type supported: " << input_types.size() << "\n";
    for (VecOfString::size_type i = 0; i < input_types.size(); ++i)
    {
        cout << setw(4) << i << " " << input_types[i] << "\n";
    }

    VecOfString output_types = IO::FrameWriterFactory::instance().getSubscribed();
    cout << "Output type supported: " << output_types.size() << "\n";
    for (VecOfString::size_type i = 0; i < output_types.size(); ++i)
    {
        cout << setw(4) << i << " " << output_types[i] << "\n";
    }

    return 0;
}
