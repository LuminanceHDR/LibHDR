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
 */

#include "libhdr/channel.h"

using namespace std;

namespace LibHDR
{
Channel::Channel(int width, int height, ChannelName channel_name):
    MatrixOfFloats(width, height),
    m_ChannelName(channel_name)
{
    //std::cout << "Channel constructor (" << name->data() << ")" << std::endl;
}

// copy constructor
Channel::Channel(const Channel& rhs):
    MatrixOfFloats(rhs),
    m_ChannelName(rhs.m_ChannelName)
{ }
     
// Assignment operator
Channel& Channel::operator=(const Channel& rhs)
{
    if (this == &rhs) return *this; // check self-assignment

    // Base class
    this->MatrixOfFloats::operator=(rhs);

    m_ChannelName = rhs.m_ChannelName;

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
    this->MatrixOfFloats::swap(other);

    // Channel data member specialization
    swap(m_ChannelName, other.m_ChannelName);
}

void swap(Channel& a, Channel& b)
{
    a.swap(b);
}

int Channel::getWidth() const
{
    return MatrixOfFloats::getCols();
}

int Channel::getHeight() const
{
    return MatrixOfFloats::getRows();
}

Channel::ChannelName Channel::getName() const
{
    return m_ChannelName;
}

bool Channel::isName(Channel::ChannelName channel_name) const
{
    return ((m_ChannelName == channel_name)? true : false);
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

