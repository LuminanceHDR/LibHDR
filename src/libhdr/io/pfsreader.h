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

#ifndef LIBHDR_PFSREADER
#define LIBHDR_PFSREADER

#include <string>
#include <vector>

#include "libhdr_dlldefines.h"
#include "libhdr/io/framereader.h"
#include "libhdr/io/pfscommon.h"

namespace LibHDR
{
namespace IO
{

class LIBHDR_API PFSReader: public FrameReader //, public PFSCommon
{
public:
    PFSReader();
    ~PFSReader();

    void open(std::string filename_);
    void close();
    Frame* readFrame(const Settings& settings_);

    bool isOpen();

    static std::vector<std::string> getID();
};

} // namespace IO
} // namespace LibHDR

#endif // LIBHDR_PFSREADER
