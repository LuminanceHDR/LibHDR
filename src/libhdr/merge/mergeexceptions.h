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

#ifndef LIBHDR_MERGEEXCEPTIONS_H
#define LIBHDR_MERGEEXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace LibHDR
{
namespace Merge
{
//!
//! \brief This exception is raised when the input set of images
//! for the merge algorithm do not have the same size
class MismatchImagesException : public std::runtime_error
{
public:
    MismatchImagesException(const std::string& msg = "");
};

//! \brief This exception is raised when an empty set of input images
//! is given to the merge operator
class NoImagesException : public std::runtime_error
{
public:
    NoImagesException(const std::string& msg = "");
};

}
}

#endif // LIBHDR_MERGEEXCEPTIONS_H
