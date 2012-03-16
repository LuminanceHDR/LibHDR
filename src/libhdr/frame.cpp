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

#include "frame.h"

#include <functional>
#include <algorithm>

namespace LibHDR
{

Frame::Frame():
    m_BitPerSample(BPS_0),
    m_SampleType(UNSPEC)
{}

Frame::Frame(const Frame& rhs)
{
    m_BitPerSample = rhs.m_BitPerSample;
    m_SampleType = rhs.m_SampleType;
}

void Frame::swap(Frame& rhs)
{
    using std::swap;

    swap(m_BitPerSample, rhs.m_BitPerSample);
    swap(m_SampleType, rhs.m_SampleType);
}

Frame::BitPerSample Frame::getBitPerSample() const
{
    return m_BitPerSample;
}

void Frame::setBitPerSample(BitPerSample bps)
{
    m_BitPerSample = bps;
}

Frame::SampleType Frame::getSampleType() const
{
    return m_SampleType;
}

void Frame::setSampleType(SampleType sample_type)
{
    m_SampleType = sample_type;
}

void swap(Frame& a, Frame& b)
{
    a.swap(b);
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
