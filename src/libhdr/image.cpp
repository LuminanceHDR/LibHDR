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

#include "image.h"

namespace LibHDR
{
using namespace std;

// ctor
Image::Image(int width, int height, ImageType image_type):
    MatrixOfPixels(height, width),
    Frame(),
    m_ImageType(image_type)
{ }

// copy ctor
Image::Image(const Image& rhs):
    MatrixOfPixels(rhs),
    Frame(rhs),
    m_Tags(rhs.m_Tags),
    m_ImageType(rhs.m_ImageType)
{ }

// assignment operator
Image& Image::operator=(const Image& rhs)
{
    // check self-assignment
    if (this == &rhs) return *this;

    // Base class
    MatrixOfPixels::operator=(rhs);

    m_Tags = rhs.m_Tags;
    m_ImageType = rhs.m_ImageType;

    return *this;
}

// dtor
Image::~Image()
{
    // std::cout << "Frame::~Frame()" << std::endl;
}

void Image::swap(Image& other)
{
    using std::swap;

    // Base class swap
    MatrixOfPixels::swap(other);

    // Channel data member specialization
    m_Tags.swap(other.m_Tags);
    swap(m_ImageType, other.m_ImageType);
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

void Image::cloneTags(const Image& other)
{
    this->m_Tags = other.m_Tags;
}

int Image::getWidth() const
{
    return MatrixOfPixels::getCols();
}

int Image::getHeight() const
{
    return MatrixOfPixels::getRows();
}

TagContainer& Image::getTags()
{
    return m_Tags;
}

const TagContainer& Image::getTags() const
{
    return m_Tags;
}


Image::ImageType Image::getImageType() const
{
    return m_ImageType;
}

void Image::setImageType(ImageType image_type)
{
    m_ImageType = image_type;
}

const Pixel* Image::pixels(const float* data)
{
    return reinterpret_cast<const Pixel*>(data);
}

Pixel* Image::pixels(float* data)
{
    return reinterpret_cast<Pixel*>(data);
}


void swap(Image& a, Image& b)
{
    a.swap(b);
}

} // namespace LibHDR

namespace std
{
template<>
void swap<LibHDR::Image>(LibHDR::Image& a, LibHDR::Image& b)
{
    a.swap(b);
}
}

