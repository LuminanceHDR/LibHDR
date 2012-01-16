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
Channel::Channel(int width, int height, ChannelType channel_type):
    MatrixOfFloats(width, height),
    m_ChannelName(channel_type),
    m_IsSynchronized(false),
    m_FatherFrame(NULL)
{
    //std::cout << "Channel constructor (" << name->data() << ")" << std::endl;
}

// copy constructor
Channel::Channel(const Channel& rhs):
    MatrixOfFloats(rhs),
    m_ChannelName(rhs.m_ChannelName),
    m_IsSynchronized(false),
    m_FatherFrame(NULL)
{ }
     
// Assignment operator
Channel& Channel::operator=(const Channel& rhs)
{
    if (this == &rhs) return *this; // check self-assignment

    // Base class
    MatrixOfFloats::operator=(rhs);

    m_ChannelName = rhs.m_ChannelName;
    // TODO: finalize the assignment operator to take into accout the presence of the synchronization command

    return *this;
}

Channel::~Channel()
{
    if ( m_IsSynchronized ) this->synchronize();
    //std::cout << "Channel destructor (" << name->data() << ")" << std::endl;
}

void Channel::swap(Channel& other)
{
    using std::swap;

    // Base class swap
    MatrixOfFloats::swap(other);

    // Channel data member specialization
    swap(m_ChannelName, other.m_ChannelName);
    swap(m_FatherFrame, other.m_FatherFrame);
    swap(m_IsSynchronized, other.m_IsSynchronized);
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

Channel::ChannelType Channel::getName() const
{
    return m_ChannelName;
}

bool Channel::isName(Channel::ChannelType channel_type) const
{
    return ((m_ChannelName == channel_type)? true : false);
}

bool Channel::isSynchronized()
{
    return m_IsSynchronized;
}

void Channel::setSynchronization(bool b)
{
    m_IsSynchronized = b;
}

void Channel::synchronize()
{
    // this function writes into the the pointed Frame the values into this Channel

}

void Channel::setFrame(Frame* frame)
{
    //bool status = frame->bindChannel(this);
    //if (

}

Frame* Channel::hasFrame()
{
    return m_FatherFrame;
}

void Channel::unsetFrame()
{
    if ( m_FatherFrame == NULL ) return;

    // else 
    // unsubscribe frame from its Father and then set internal structure to zero
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

