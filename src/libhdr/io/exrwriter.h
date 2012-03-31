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

#ifndef LIBHDR_EXRWRITER_H
#define LIBHDR_EXRWRITER_H
//!
//! \file exrwriter.h
//! \brief EXR Writer for \c LibHDR::Image
//! \date 2012-03-25
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \since 0.0
//!
#include <string>
#include <vector>
#include <boost/scoped_ptr.hpp>

#include "libhdr/io/framewriter.h"
#include "libhdr/io/ioexceptions.h"
#include "libhdr/settings.h"

namespace LibHDR
{
namespace IO
{

struct EXRWriterImpl;
//!
//! \class EXRWriter
//! \brief Writes file with extension .exr
//!
class EXRWriter : public FrameWriter
{
public:
    //!
    //!
    EXRWriter();
    //!
    //!
    virtual ~EXRWriter();
    //!
    //!
    void open(const std::string& filename);
    //!
    //!
    bool writeFrame(const ImagePtr frame, const Settings& settings);
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
    boost::scoped_ptr<EXRWriterImpl> m_EXRWriterImpl;
};

}
}


#endif // LIBHDR_EXRWRITER_H
