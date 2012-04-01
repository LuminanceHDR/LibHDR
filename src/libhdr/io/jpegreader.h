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

#ifndef LIBHDR_JPEGREADER_H
#define LIBHDR_JPEGREADER_H
//!
//! \file jpegreader.h
//! \brief
//! \date 2012-03-31
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \since 0.0
//!
#include <vector>
#include <string>
#include <boost/scoped_ptr.hpp>

#include "libhdr/io/framereader.h"
#include "libhdr/io/ioexceptions.h"
#include "libhdr/settings.h"

namespace LibHDR
{
namespace IO
{
class JpegReaderImpl;

//!
//! \class MagickReader
//! \brief Reads files with multiple extension, but .jpg in particular
//!
class LIBHDR_API JpegReader : public FrameReader
{
public:
    JpegReader();
    ~JpegReader();

    void open(const std::string& filename);
    void close();
    ImagePtr readFrame(const Settings& settings);

    bool isOpen();

    static std::vector<std::string> getID();

private:
    boost::scoped_ptr<JpegReaderImpl> impl_;
};

}   // namespace IO
}   // namespace LibHDR

#endif // LIBHDR_JPEGREADER_H
