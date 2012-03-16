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
 
#ifndef LIBHDR_CHANNEL
#define LIBHDR_CHANNEL

#include "libhdr_dlldefines.h"
#include "libhdr/matrix.h"
#include "libhdr/frame.h"

namespace LibHDR
{
class Image; // forward declaration

typedef Matrix<float> MatrixOfFloats;

class LIBHDR_API Channel : public MatrixOfFloats, public Frame
{
public:
    enum ChannelType
    {
        ALPHA,
        R_RGB,
        G_RGB,
        B_RGB,
        R_sRGB,
        G_sRGB,
        B_sRGB,
        X_XYZ,
        Y_XYZ,
        Z_XYZ,
        Y_YUV,
        U_YUV,
        V_YUV,
        Y_Yxy,
        x_Yxy,
        y_Yxy,
        UNKNOWN
    };

public:
    Channel(int width, int height, ChannelType channel_type = UNKNOWN);
    Channel(const Channel& rhs);
    Channel& operator=(const Channel& rhs);
    virtual ~Channel();

    void swap(Channel&);

    //! \brief Gets width of the Channel (in pixels).
    int getWidth() const;

    //! \brief Gets height of the Channel (in pixels).
    int getHeight() const;

    //! \brief Return name of the Channel
    ChannelType getType() const;
    //! \brief Check if the name is the one specified
    bool isType(ChannelType channel_type) const;
    //! \brief Set Channel Type
    void setType(ChannelType channel_type);

    //! \return return if the Channel is synchronized with a frame
    bool isSynchronized();
    //! \brief set the synchronization mode between this Channel and the Frame it belongs to (if any)
    void setSynchronization(bool);
    //! \brief Explictly synchronize this Channel with the Frame it belongs to
    //! synchronization copies the content of this Channel into the corrisponding position of the pointed Frame
    void synchronize();

    //! \brief set the Frame this Channel will belong to
    void setFrame(Image* frame);
    //! \brief return a pointer to the Frame this Channel belong to
    //! \return NULL if this Channel does not belong to any Frame
    Image* hasFrame();
    //! \brief reset the pointed Frame
    void unsetFrame();

private:
    ChannelType m_ChannelType;
    bool m_IsSynchronized;
    Image* m_FatherFrame;
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
