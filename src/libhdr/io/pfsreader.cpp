/**
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
 * 
 * @author Davide Anastasia <davideanastasia@users.sourceforge.net>
 *  Original work by Rafal Mantiuk, <mantiuk@mpi-sb.mpg.de> for PFSTOOLS
 *
 */

#include "libhdr/io/pfsreader.h"
//#include "libhdr/io/ioexceptions.h"

#include <iostream>



namespace
{
using namespace LibHDR::Template;
using namespace LibHDR::IO;

bool subscribe2factory()
{
    // get pointer to FrameReaderFactory
    FrameReaderFactory::HoldType& factory = FrameReaderFactory::instance();

    std::vector<std::string> id_ = PFSReader::getID();
    for ( int idx = 0; idx < id_.size(); ++idx)
    {
        factory.subscribe(id_[idx], createInstance<FrameReader, PFSReader>);
    }
}

static bool factory_subscription = subscribe2factory();
}

namespace LibHDR
{
namespace IO
{


PFSReader::PFSReader()
{}

PFSReader::~PFSReader()
{}

void PFSReader::open(std::string _filename)
{

}

Frame* PFSReader::readFrame(const Settings& settings)
{
    return NULL;
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
    std::vector<std::string> id_;

    id_.push_back("pfs");

    return id_;
}
    
} // namespace IO
} // namespace LibHDR

