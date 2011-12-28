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
 */
 
#ifndef LIBHDR_CHANNEL
#define LIBHDR_CHANNEL

#include "libhdr_dlldefines.h"
#include "libhdr/matrix.h"

namespace LibHDR
{
class LIBHDR_API Channel : public MatrixOfFloats
{
public:
    enum ChannelName
    {
        RED_CHANNEL,
        GREEN_CHANNEL,
        BLUE_CHANNEL,
        ALPHA_CHANNEL,
        X_CHANNEL,
        Y_CHANNEL,
        Z_CHANNEL,
        u_CHANNEL,
        v_CHANNEL,
        UNKNOWN
    };

private:
    ChannelName m_ChannelName;

public:
    Channel(int width, int height, ChannelName channel_name = UNKNOWN);
    Channel(const Channel& rhs);
    Channel& operator=(const Channel& rhs);
    virtual ~Channel();

    void swap(Channel&);

    //! \brief Gets width of the channel (in pixels).
    int getWidth() const;

    //! \brief Gets height of the channel (in pixels).
    int getHeight() const;

    //! \brief Return name of the channel
    ChannelName getName() const;
    //! \brief Check if the name is the one specified
    bool isName(ChannelName channel_name) const;
};

//! \brief Swap Channel a with Channel b
void swap(Channel& a, Channel& b);
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
