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
 */

#include "Channel.h"

using namespace std;

namespace LibHDR
{
Channel::Channel(int width, int height, std::string name):
    Array2D(width, height),
    m_ChannelName(name)
{
    //std::cout << "Channel constructor (" << name->data() << ")" << std::endl;
}

// copy constructor
Channel::Channel(const Channel& rhs):
    Array2D(rhs),
    m_ChannelName(rhs.m_ChannelName),
    m_Tags(rhs.getTags())
{ }
     
// Assignment operator
Channel& Channel::operator=(const Channel& rhs)
{
    if (this == &rhs) return *this; // check self-assignment

    // Base class
    this->Array2D::operator=(rhs);

    m_ChannelName = rhs.m_ChannelName;

    // remove all tags & copy tags from rhs (all done by operator=)
    m_Tags = rhs.getTags();

    return *this;
}

Channel::~Channel()
{
    //std::cout << "Channel destructor (" << name->data() << ")" << std::endl;
}

void Channel::swap(Channel& other)
{
    using std::swap;

    // Base class swap
    this->Array2D::swap(other);

    // Channel data member specialization
    m_ChannelName.swap(other.m_ChannelName);
    m_Tags.swap(other.m_Tags);
}

void Channel::cloneTags(const Channel& other)
{
    this->m_Tags = other.m_Tags;
}

void swap(Channel& a, Channel& b)
{
    a.swap(b);
}

} // namespace LibHDR

namespace std
{
template<>
void swap<LibHDR::Channel>(LibHDR::Channel& a, LibHDR::Channel& b)
{
    a.swap(b);
}
}

