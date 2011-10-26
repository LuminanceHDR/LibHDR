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
        m_Channels(rhs.m_Channels) // this one makes a mess!
    { }
    
    // assignment operator
    // default behaviour... in fact this function can also be removed!
    Frame& Frame::operator=(const Frame& rhs)
    {
        m_Width = rhs.m_Width;
        m_Height = rhs.m_Height;
        m_Tags = rhs.m_Tags;
        m_Channels = rhs.m_Channels; // this one makes a mess!

        return *this;
    }

    // dtor
    Frame::~Frame()
    {
        // deallocate Channels from ChannelMap
        for (ChannelMap::iterator it = m_Channels.begin(); it != m_Channels.end(); it++)
        {
            delete it->second;
        }
        // std::cout << "Frame::~Frame()" << std::endl;
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
        X = it->second;

        // find Y
        it = m_Channels.find("Y");
        if ( it == m_Channels.end() )
        {
            X = Y = Z = NULL;
            return;
        }
        Y = it->second;

        // find Y
        it = m_Channels.find("Z");
        if ( it == m_Channels.end() )
        {
            X = Y = Z = NULL;
            return;
        }
        Z = it->second;
    }

    void Frame::createXYZChannels( Channel* &X, Channel* &Y, Channel* &Z )
    {
        X = createChannel("X");
        Y = createChannel("Y");
        Z = createChannel("Z");
    }

    Channel* Frame::getChannel( std::string name )
    {
        ChannelMap::iterator it = m_Channels.find(name);
        if ( it == m_Channels.end() )
            return NULL;
        else
            return it->second;
    }

    Channel* Frame::createChannel( std::string name )
    {
        ChannelMap::iterator it = m_Channels.find(name);

        if ( it != m_Channels.end() )
        {
            return it->second;
        }
        else
        {
            Channel* ch = new Channel( m_Width, m_Height, name );
            m_Channels.insert( std::pair<std::string, Channel*>(name, ch) );

            return ch;
        }
    }

    /*
    void Frame::removeChannel( Channel *ch )
    {
        assert( ch != NULL );
        ChannelMap::iterator it = m_Channels.find( ch->getName() );
        assert( it != m_Channels.end() && it->second == ch );

        m_Channels.erase( it );
        delete ch;
    }
    */
} // namespace LibHDR

