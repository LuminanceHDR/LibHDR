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
 *
 */

#ifndef LIBHDR_IOEXCEPTION
#define LIBHDR_IOEXCEPTION

#include <string>
#include <exception>
#include <stdexcept>

namespace LibHDR
{
namespace IO
{

class OpenException: public std::runtime_error
{
public:
    OpenException(const std::string& msg = "");
};

class CloseException: public std::runtime_error
{
public:
    CloseException(const std::string& msg = "");
};

class ReadException: public std::runtime_error
{
public:
    ReadException(const std::string& msg = "");
};

class WriteException: public std::runtime_error
{
public:
    WriteException(const std::string& msg = "");
};
    
} // namespace IO
} // namespace LibHDR


#endif

