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

#include "FrameReader.h"
#include "IStrategyReader.h"

namespace LibHDR
{

namespace IO
{

FrameReader::FrameReader()
{
    m_ReaderImpl = NULL;
}

FrameReader::FrameReader(std::string _filename)
{
    open(_filename);
}

FrameReader::~FrameReader()
{
    if ( m_ReaderImpl )
    {
        m_ReaderImpl->close();
        delete m_ReaderImpl;
    }
}

void FrameReader::getFrameType(std::string _filename)
{

}

void FrameReader::open(std::string _filename)
{
    /*
    * check if open already, close and open the new one
    */

//    switch (getFrameType(_filename))
//    {
//    default:
//    {
//        ;
//    }
//        break;
//    }
}

Frame* FrameReader::readFrame()
{
    return NULL;
}

void FrameReader::close()
{
    if ( m_ReaderImpl ) m_ReaderImpl->close();
}

bool FrameReader::isOpen()
{
    if ( m_ReaderImpl )  return m_ReaderImpl->isOpen();
    return false;
}

} // end namespace IO
} // end namespace LibHDR
