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

#ifndef LIBHDR_FRAME
#define LIBHDR_FRAME

#include <string>

#include "DLLDefines.h"
#include "Channel.h"
#include "Tag.h"

namespace LibHDR
{
    /**
     * Interface representing a single PFS frame. Frame may contain 0
     * or more channels (e.g. color XYZ, depth channel, alpha
     * channnel). All the channels are of the same size. Frame can
     * also contain additional information in tags (see getTags).
     */
    class LIBHDR_API Frame
    {
    protected:
        int             m_Width;
        int             m_Height;

        TagContainer    m_Tags;
        ChannelMap      m_Channels;

    public:
        Frame(int width, int height);
        Frame(const Frame&);
        Frame& operator=(const Frame&);
        virtual ~Frame();

        void swap(Frame&);

        /**
         * Gets width of the channels (in pixels).
         */
        int getWidth() const;

        /**
         * Gets height of the channels (in pixels).
         */
        int getHeight() const;

        /**
         * Gets color channels in XYZ color space. May return NULLs
         * if such channels do not exist. Values assigned to
         * X, Y, Z are always either all NULLs or valid pointers to
         * channels.
         *
         * @param X [out] a pointer to store X channel in
         * @param Y [out] a pointer to store Y channel in
         * @param Z [out] a pointer to store Z channel in
         */
        void getXYZChannels( Channel* &X, Channel* &Y, Channel* &Z );

        /**
         * Creates color channels in XYZ color space. If such channels
         * already exists, returns existing channels, rather than
         * creating new ones.  Note, that nothing can be assumed about
         * the content of each channel.
         *
         * @param X [out] a pointer to store X channel in
         * @param Y [out] a pointer to store Y channel in
         * @param Z [out] a pointer to store Z channel in
         */
        void createXYZChannels( Channel* &X, Channel* &Y, Channel* &Z );

        /**
         * Gets a named channel.
         *
         * @param name [in] name of the channel.
         * @return channel or NULL if the channel does not exist
         */
        Channel* getChannel( std::string name );
        const Channel* getChannel( std::string name ) const;

        /**
         * Creates a named channel. If the channel already exists, returns
         * existing channel.
         *
         * Note that new channels should be created only for the first
         * frame. The channels should not changes for the subsequent
         * frames of a sequence.
         *
         * @param name [in] name of the channel.
         * @return existing or newly created channel
         */
        Channel* createChannel( std::string name );

        /**
         * Removes a channel. If a channel with name "name" does not exist, 
         * function returns without doing anything
         *
         * @param name [in] name of the channel that should be removed.
         */
        void removeChannel( std::string name );

        /**
         *
         * Returns STL Map of Channels.
         *
         */
        ChannelMap& getChannels();
        const ChannelMap& getChannels() const;

        /**
         * Returns reference to TagContainer that can be used
         * to access or modify tags associated with this Frame object.
         */
        TagContainer& getTags();
        const TagContainer& getTags() const;
    };

    // Inline functions
    inline int Frame::getWidth() const
    {
        return m_Width;
    }

    inline int Frame::getHeight() const
    {
        return m_Height;
    }

    inline ChannelMap& Frame::getChannels()
    {
        return m_Channels;
    }

    inline const ChannelMap& Frame::getChannels() const
    {
        return m_Channels;
    }

    inline TagContainer& Frame::getTags()
    {
        return m_Tags;
    }

    inline const TagContainer& Frame::getTags() const
    {
        return m_Tags;
    }
}

namespace std
{
/*
  * Specialization of std::swap for Frame
  */
template<>
void swap<LibHDR::Frame>(LibHDR::Frame& a, LibHDR::Frame& b);
}

#endif // LIBHDR_FRAME
