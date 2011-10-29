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
#include <map>

#include "Frame.h"

namespace LibHDR
{
    using namespace std;
    
    // ctor
    Frame::Frame( int width, int height ):
    m_Width( width ), m_Height( height )
    { }

    // copy ctor
    Frame::Frame(const Frame& rhs):
        m_Width(rhs.m_Width),
        m_Height(rhs.m_Height),
        m_Tags(rhs.m_Tags),
        m_Channels(rhs.m_Channels)
    { }
    
    // assignment operator
    // default behaviour... in fact this function can also be removed!
    Frame& Frame::operator=(const Frame& rhs)
    {
        m_Width = rhs.m_Width;
        m_Height = rhs.m_Height;
        m_Tags = rhs.m_Tags;
        m_Channels = rhs.m_Channels;

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

        swap(m_Width, other.m_Width);
        swap(m_Height, other.m_Height);
        swap(m_Tags, other.m_Tags);
        swap(m_Channels, other.m_Channels);
    }

    void Frame::getXYZChannels( Channel* &X, Channel* &Y, Channel* &Z )
    {
        ChannelMap::iterator it;

        // find X
        it = m_Channels.find("X");
        if ( it == m_Channels.end() )
        {
            X = Y = Z = NULL;
            return;
        }
        X = &it->second;

        // find Y
        it = m_Channels.find("Y");
        if ( it == m_Channels.end() )
        {
            X = Y = Z = NULL;
            return;
        }
        Y = &it->second;

        // find Y
        it = m_Channels.find("Z");
        if ( it == m_Channels.end() )
        {
            X = Y = Z = NULL;
            return;
        }
        Z = &it->second;
    }

    void Frame::createXYZChannels( Channel* &X, Channel* &Y, Channel* &Z )
    {
        X = createChannel("X");
        Y = createChannel("Y");
        Z = createChannel("Z");
    }

    const Channel* Frame::getChannel( std::string name ) const
    {
        ChannelMap::const_iterator it = m_Channels.find(name);
        if ( it == m_Channels.end() )
            return NULL;
        else
            return &it->second;
    }

    Channel* Frame::getChannel( std::string name )
    {
        // Effective C++: Item 3
        return const_cast<Channel*>(static_cast<const Frame&>(*this).getChannel(name));
    }

    Channel* Frame::createChannel( std::string name )
    {
        ChannelMap::iterator it = m_Channels.find(name);
        if ( it != m_Channels.end() )
        {
            return &it->second;
        }
        else
        {
            return &(*(m_Channels.insert( ChannelPair(name, Channel( m_Width, m_Height, name )) ).first)).second;
        }
    }

    void Frame::removeChannel( std::string name )
    {
        m_Channels.erase(name);
    }

    bool Frame::isChannel( std::string name ) const
    {
        ChannelMap::const_iterator it = m_Channels.find(name);
        return ( it != m_Channels.end() )? true: false;
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

