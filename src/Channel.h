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
#include <list>

#include "DLLDefines.h"
#include "array2d.h"
#include "Tag.h"

namespace LibHDR
{
class LIBHDR_API Channel : public Array2D
{
private:
    std::string m_ChannelName;
    TagContainer m_Tags;

public:
    explicit Channel(int width, int height, std::string name);
    Channel(const Channel& rhs);
    Channel& operator=(const Channel& rhs);
    virtual ~Channel();

    void swap(Channel&);

    /**
     * Returns TagContainer that can be used to access or modify
     * tags associated with this Channel object.
     */
    TagContainer& getTags();
    const TagContainer& getTags() const;

    /**
     * Clones "other"'s tags into current object
     */
    void cloneTags(const Channel& other);

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
    bool isName(std::string) const;
};

// Inline functions
inline TagContainer& Channel::getTags()
{
    return m_Tags;
}

inline const TagContainer& Channel::getTags() const
{
    return m_Tags;
}

inline int Channel::getWidth() const
{
    return Array2D::getCols();
}

inline int Channel::getHeight() const
{
    return Array2D::getRows();
}

inline std::string Channel::getName() const
{
    return m_ChannelName;
}

inline bool Channel::isName(std::string name) const
{
    return ((m_ChannelName == name)? true : false);
}

void swap(Channel& a, Channel& b);

typedef std::list<Channel> ChannelList;
}

namespace std
{
/*
  * Specialization of std::swap for Channel
  */
template<>
void swap<LibHDR::Channel>(LibHDR::Channel& a, LibHDR::Channel& b);
}

#endif //LIBHDR_CHANNEL
