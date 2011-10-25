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
 
#ifndef LIBHDR_CHANNEL
#define LIBHDR_CHANNEL

#include <string>
#include <map>

#include "DLLDefines.h"
#include "array2d.h"
//#include "tag.h"

namespace LibHDR
{
    class LIBHDR_API Channel : public Array2D
    {
    protected:
        std::string m_ChannelName;

        //TagContainer *tags;

    public:
        Channel(int width, int height, std::string name);

        virtual ~Channel();

        /**
        * Returns TagContainer that can be used to access or modify
        * tags associated with this Channel object.
        */
        //TagContainer *getTags();

        /**
        * Gets width of the channel (in pixels).
        * This is a synonym for Array2D::getCols().
        */
        int getWidth() const;

        /**
        * Gets height of the channel (in pixels).
        * This is a synonym for Array2D::getRows().
        */
        int getHeight() const;

        /**
        * Gets name of the channel.
        */
        std::string getName() const;
    };

    // Inline functions
    inline int Channel::getWidth() const
    {
        return Array2D::getCols();
    }

    inline int Channel::getHeight() const
    {
        return Array2D::getRows();
    }

    //------------------------------------------------------------------------------
    // Map of channels
    //------------------------------------------------------------------------------
    struct string_cmp: public std::binary_function<std::string,std::string,bool>
    {
        bool operator()(std::string s1, std::string s2) const
        {
            return (s1.compare(s2) < 0);
        }
    };

    typedef std::map<std::string, Channel*, string_cmp> ChannelMap; //, str_cmp> ;

    struct compareChannels: public std::binary_function<std::string,std::string,bool>
    {
        bool operator()(const Channel& c1, const Channel& c2) const
        {
            return ((c1.getName()).compare(c2.getName()) < 0);
        }
    };

    typedef std::map<Channel&, compareChannels> ChannelSet;
}


#endif //LIBHDR_CHANNEL
