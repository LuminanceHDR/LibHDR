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


#include <iostream>
#include <functional>
#include <algorithm>
#include <string>

#include "libhdr/frame.h"

namespace LibHDR
{
using namespace std;

// ctor
Frame::Frame(int width, int height, FrameType frame_type):
    MatrixOfPixels(height, width),
    m_FrameType(frame_type)
{ }

// copy ctor
Frame::Frame(const Frame& rhs):
    MatrixOfPixels(rhs),
    m_Tags(rhs.m_Tags),
    m_FrameType(rhs.m_FrameType)
{ }

// assignment operator
Frame& Frame::operator=(const Frame& rhs)
{
    // check self-assignment
    if (this == &rhs) return *this;

    // Base class
    MatrixOfPixels::operator=(rhs);

    m_Tags = rhs.m_Tags;
    m_FrameType = rhs.m_FrameType;

    return *this;
}

// dtor
Frame::~Frame()
{
    // std::cout << "Frame::~Frame()" << std::endl;
}

void Frame::swap(Frame& other)
{
    using std::swap;

    // Base class swap
    MatrixOfPixels::swap(other);

    // Channel data member specialization
    m_Tags.swap(other.m_Tags);
    swap(m_FrameType, other.m_FrameType);
}

//const Channel& Frame::getChannel( std::string name ) const
//{
//    ChannelList::const_iterator it = find_if(m_Channels.begin(), m_Channels.end(), std::bind2nd( std::mem_fun_ref( &Channel::isName ), name));
//    if ( it == m_Channels.end() )
//        throw ChannelNotFound(name); // throw
//    else
//        return *it;
//}

//Channel& Frame::getChannel( std::string name )
//{
//    // Effective C++: Item 3
//    return const_cast<Channel&>(static_cast<const Frame&>(*this).getChannel(name));
//}

void Frame::cloneTags(const Frame& other)
{
    this->m_Tags = other.m_Tags;
}

int Frame::getWidth() const
{
    return MatrixOfPixels::getCols();
}

int Frame::getHeight() const
{
    return MatrixOfPixels::getRows();
}

TagContainer& Frame::getTags()
{
    return m_Tags;
}

const TagContainer& Frame::getTags() const
{
    return m_Tags;
}

void swap(Frame& a, Frame& b)
{
    a.swap(b);
}

} // namespace LibHDR

namespace std
{
template<>
void swap<LibHDR::Frame>(LibHDR::Frame& a, LibHDR::Frame& b)
{
    a.swap(b);
}
}

