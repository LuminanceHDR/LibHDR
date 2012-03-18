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

#ifndef LIBHDR_IMAGE
#define LIBHDR_IMAGE

#include <string>

#include "libhdr_dlldefines.h"
#include "libhdr/matrix.h"
#include "libhdr/tag.h"
#include "libhdr/pixel.h"
#include "libhdr/frame.h"

namespace LibHDR
{
class Channel;  // forward declaration

//! \class Frame
//! \brief Class representing a single frame. Every frame contains also additional information in tags
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
class LIBHDR_API Image: public Matrix<Pixel>, public Frame
{
private:
    //! \typedef MatrixOfPixels as \c Matrix of \c Pixel
    typedef Matrix<Pixel> MatrixOfPixels;

public:
    //! \enum define the frame type of the current image (whether available)
    enum ImageType
    {
        UNDEF = 0,
        RGB = 1,
        sRGB = 2,
        XYZ = 3,
        YUV = 4,
        Yxy = 5
    };

public:
    Image(int width, int height, ImageType frame_type = RGB);
    Image(const Image&);
    Image& operator=(const Image&);
    virtual ~Image();

    //! \brief Swap \c Image
    void swap(Image&);

    //! \brief Gets width of the \c Image (in pixels).
    int getWidth() const;

    //! \brief Gets height of the \c Image (in pixels).
    int getHeight() const;

    ////! \brief Gets a named channel
    ////! \param name [in] name of the channel.
    ////! \return channel or NULL if the channel does not exist
    //Channel& getChannel( std::string name );
    //const Channel& getChannel( std::string name ) const;

    //! \brief handle to a the internal tag container
    //! \return reference to TagContainer
    TagContainer& getTags();

    //! \brief handle to a the internal tag container
    //! \return const reference to TagContainer
    const TagContainer& getTags() const;

    //! \brief Clones "other"'s tags into current object
    void cloneTags(const Image& other);

    //! \brief Return the \c ImageType
    ImageType getImageType() const;
    //! \brief set the \c ImageType
    void setImageType(ImageType image_type);

private:
    TagContainer    m_Tags;
    ImageType       m_ImageType;
};

//! \brief swaps \c Image a with \c Image b
void swap(Image& a, Image& b);

//! \typedef Shared pointer to \c Image
typedef boost::shared_ptr<Image> ImagePtr;

} // namespace LibHDR

namespace std
{

//! \brief Specialization of std::swap for \c Image
template<>
void swap<LibHDR::Image>(LibHDR::Image& a, LibHDR::Image& b);
}

#endif // LIBHDR_IMAGE
