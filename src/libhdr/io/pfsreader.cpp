/*
 * This file is a part of LibHDR package.
 * ---------------------------------------------------------------------- 
 * Copyright (C) 2011 Davide Anastasia
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

#include "libhdr/io/pfsreader.h"
#include "libhdr/io/framereader.aux.h"
//#include "libhdr/io/ioexceptions.h"

#include <iostream>
#include <stdio.h>

namespace LibHDR
{
namespace IO
{

PFSReader::PFSReader()
{}

PFSReader::~PFSReader()
{}

void PFSReader::open(const std::string& /*filename*/)
{

}

ImagePtr PFSReader::readFrame(const Settings& /*settings*/)
{
    return ImagePtr();
}
    
void PFSReader::close()
{

}

bool PFSReader::isOpen()
{
    return false;
}

std::vector<std::string> PFSReader::getID()
{
    std::vector<std::string> id;

    id.push_back("pfs");

    return id;
}

REGISTER_FRAMEREADER(PFSReader)

} // namespace IO
} // namespace LibHDR

