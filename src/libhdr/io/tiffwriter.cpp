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

namespace LibHDR
{
namespace IO
{

TIFFWriter::TIFFWriter()
{}

TIFFWriter::~TIFFWriter()
{}

void TIFFWriter::open(const std::string& filename)
{}

bool TIFFWriter::writeFrame(const Frame& frame, const Settings& settings)
{
    return true;
}

void TIFFWriter::close()
{}

bool TIFFWriter::isOpen()
{
    return false;
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
