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

#ifndef LIBHDR_FRAMEREADER_H
#define LIBHDR_FRAMEREADER_H

//! \file framereader.h
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \date December 2011
//! \since 0.0

#include <string>
#include <boost/utility.hpp>

#include "libhdr_dlldefines.h"
#include "libhdr/io/iocommon.h"
#include "libhdr/coreobject.h"
#include "libhdr/settings.h"

#include "libhdr/template/objectfactory.h"
#include "libhdr/template/singleton.h"

namespace LibHDR
{
class Frame;

namespace IO
{
//!
//! \class FrameReader
//! \brief Base class interface for object subscribed to the FrameReaderFactory
class LIBHDR_API FrameReader:
        public CoreObject,
        public boost::noncopyable
{
public:
    //! \brief empty constructor for the base class FrameReader
    FrameReader();
    //! \brief empty virtual destructor for the base class FrameReader
    virtual ~FrameReader();

    //! \brief open a file of name filename
    virtual void open(std::string filename) = 0;

    //! \brief reads a file
    //! \param[in] settings
    //! \return Valid pointer to Frame, or NULL otherwise
    virtual Frame* readFrame(const Settings& settings) = 0;

    //! \brief closes the current file
    virtual void close() = 0;

    //! \brief Check if the current file is open
    //! \return returns true if the file is open
    virtual bool isOpen() = 0;
};

//! \typedef Defines a Singleton holder for a factory of FrameReader
typedef Template::Singleton< Template::ObjectFactory<FrameReader, std::string> > FrameReaderFactory;

} // end namespace IO
} // end namespace LibHDR

#endif // LIBHDR_FRAMEREADER_H
