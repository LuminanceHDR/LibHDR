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

#ifndef LIBHDR_TIFFWRITER_H
#define LIBHDR_TIFFWRITER_H
//!
//! \file tiffwriter.h
//! \brief
//! \date 2012-02-09
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \since 0.0
//!
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>

#include "libhdr/io/framewriter.h"
#include "libhdr/settings.h"

namespace LibHDR
{
namespace IO
{

class TIFFWriterImpl;
//!
//! \class TIFFWriter
//! \brief Writes file with extension .tif or .tiff
//!
class TIFFWriter : public FrameWriter
{
public:
    //!
    //!
    TIFFWriter();
    //!
    //!
    virtual ~TIFFWriter();
    //!
    //!
    void open(const std::string& filename);
    //!
    //!
    bool writeFrame(const Frame& frame, const Settings& settings);
    //!
    //!
    void close();
    //!
    //!
    bool isOpen();
    //!
    //! \brief Returns a vector of supported extension
    static std::vector<std::string> getID();
    //!
private:
    boost::scoped_ptr<TIFFWriterImpl> m_TIFFWriterImpl;
};

}
}


#endif // LIBHDR_TIFFWRITER_H
