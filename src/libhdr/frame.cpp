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
 *  Derived from the original work by Rafal Mantiuk <mantiuk@mpi-sb.mpg.de> for PFSTOOLS
 *   
 */

#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
//#include <map>

#include "libhdr/frame.h"

namespace LibHDR
{
using namespace std;

// ctor
template <typename Type>
Frame<Type>::Frame( int width, int height ):
    Matrix<Type>(height, width)
{ }

// copy ctor
template <typename Type>
Frame<Type>::Frame(const Frame<Type>& rhs):
    Matrix<Type>(rhs),
    m_Tags(rhs.m_Tags)
{ }

// assignment operator
// default behaviour... in fact this function can also be removed!
template <typename Type>
Frame<Type>& Frame<Type>::operator=(const Frame<Type>& rhs)
{
    // check self-assignment
    if (this == &rhs) return *this;

    // Base class
    this->Matrix<Type>::operator=(rhs);

    m_Tags = rhs.m_Tags;

    return *this;
}

// dtor
template <typename Type>
Frame<Type>::~Frame()
{
    // std::cout << "Frame::~Frame()" << std::endl;
}

template <typename Type>
void Frame<Type>::swap(Frame<Type>& other)
{
    using std::swap;

    // Base class swap
    this->Matrix<Type>::swap(other);

    // Channel data member specialization
    m_Tags.swap(other.m_Tags);
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

template <typename Type>
void Frame<Type>::cloneTags(const Frame<Type>& other)
{
    this->m_Tags = other.m_Tags;
}

template <typename Type>
int Frame<Type>::getWidth() const
{
    return this->getCols();
}

template <typename Type>
int Frame<Type>::getHeight() const
{
    return this->getRows();
}

template <typename Type>
TagContainer& Frame<Type>::getTags()
{
    return m_Tags;
}

template <typename Type>
const TagContainer& Frame<Type>::getTags() const
{
    return m_Tags;
}

template <typename Type>
void swap(Frame<Type>& a, Frame<Type>& b)
{
    a.swap(b);
}

//! \brief explicit instantiation of class Frame
template class Frame<float>;

} // namespace LibHDR

namespace std
{
//template<>
//void swap<LibHDR::Frame>(LibHDR::Frame& a, LibHDR::Frame& b)
//{
//    a.swap(b);
//}
}

