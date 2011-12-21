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

#include "libhdr_dlldefines.h"
#include "libhdr/matrix.h"
#include "libhdr/tag.h"

namespace LibHDR
{
//! \class Template class representing a single frame. Every frame contains also additional information in tags
//! \author Davide Anastasia <davide.anastasia@users.sourceforge.net>

template <typename Type>
class Frame: public Matrix<Type>
{
public:
    Frame(int width, int height);
    Frame(const Frame<Type>&);
    Frame& operator=(const Frame<Type>&);
    virtual ~Frame();

    //! \brief Swap Frame(s)
    void swap(Frame<Type>&);

    //! \brief Gets width of the channels (in pixels).
    int getWidth() const;

    //! \brief Gets height of the channels (in pixels).
    int getHeight() const;

    //! \brief Gets a named channel
    //! \param name [in] name of the channel.
    //! \return channel or NULL if the channel does not exist
    //Channel& getChannel( std::string name );
    //const Channel& getChannel( std::string name ) const;

    //! \brief handle to a the internal tag container
    //! \return reference to TagContainer
    TagContainer& getTags();

    //! \brief handle to a the internal tag container
    //! \return const reference to TagContainer
    const TagContainer& getTags() const;

    //! \brief Clones "other"'s tags into current object
    void cloneTags(const Frame& other);

private:
    TagContainer    m_Tags;
};

//! \brief generic swap of Frame(s)
//template <typename Type>
//void swap(Frame<& a, Frame& b);
} // namespace LibHDR

namespace std
{

//! \brief Specialization of std::swap for Frame
//template<>
//void swap<LibHDR::Frame>(LibHDR::Frame& a, LibHDR::Frame& b);
}

#endif // LIBHDR_FRAME