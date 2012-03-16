/*
 * This file is a part of LibHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2012 Davide Anastasia
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

#ifndef LIBHDR_FRAME
#define LIBHDR_FRAME

#include <libhdr_dlldefines.h>

namespace LibHDR
{

class LIBHDR_API Frame
{
public:
    //! \enum define bit per sample of the source image (whether available)
    enum BitPerSample
    {
        BPS_0 = 0,
        BPS_8 = 8,
        BPS_16 = 16,
        BPS_32 = 32
    };

    //! \enum define sample type of the source image
    enum SampleType
    {
        UNSPEC = 0,
        UINT = 1,
        FLOAT = 2
    };

    //! \brief ctor
    Frame();

    //! \brief copy ctor
    Frame(const Frame& rhs);

    //! \brief Swap \c Fram
    void swap(Frame& rhs);

    //! \brief Return bit per sample, whenever available, of the source image
    BitPerSample getBitPerSample() const;
    //! \brief Set bit per sample of the current image
    void setBitPerSample(BitPerSample bps);

    //! \brief Return sample type of the current image (whenever available)
    SampleType getSampleType() const;
    //! \brief Set sample type of the current image
    void setSampleType(SampleType sample_type);

private:
    BitPerSample    m_BitPerSample;
    SampleType      m_SampleType;
};

//! \brief swaps \c Frame a with \c Frame b
void swap(Frame& a, Frame& b);

} // namespace LibHDR

namespace std
{

//! \brief Specialization of std::swap for \c Frame
//template<>
//void swap<LibHDR::Frame>(LibHDR::Frame& a, LibHDR::Frame& b);
}

#endif // LIBHDR_FRAME
