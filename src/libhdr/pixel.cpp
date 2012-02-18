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

#include "libhdr/pixel.h"

#include <sstream>
#include <iomanip>
#include <iostream>

namespace LibHDR
{

Pixel::Pixel()
{}

Pixel::Pixel(float value):
    vec4f(_mm_set1_ps(value))
{}

Pixel::Pixel(float c0, float c1, float c2, float c3):
    vec4f(_mm_set_ps(c3, c2, c1, c0))
{}

Pixel::operator uint32_t() const
{
    /*
    __m128 temp = _mm_mul_ps(vec4f, _mm_set1_ps(255.f));
    __m64 conv = _mm_cvtps_pi8(temp);
    uint32_t* pix = reinterpret_cast<uint32_t*>(&conv);

// DEBUG
    uint8_t* p = reinterpret_cast<uint8_t*>(&conv);
    std::cout << (int)p[0] << " " << (int)p[1] << " " << (int)p[2] << " " << (int)p[3] << std::endl;
// DEBUG

    return pix[0];
     */
    
    __m128 conv = _mm_mul_ps(vec4f, _mm_set1_ps(255.f));
    float* pix = reinterpret_cast<float*>(&conv);
    
    uint32_t bit8;
    uint8_t* p = reinterpret_cast<uint8_t*>(&bit8);
    
    p[0] = static_cast<uint8_t> (pix[0]);
    p[1] = static_cast<uint8_t> (pix[1]);
    p[2] = static_cast<uint8_t> (pix[2]);
    p[3] = static_cast<uint8_t> (pix[3]);
    
    // DEBUG
    //uint8_t* p = reinterpret_cast<uint8_t*>(&conv);
    //std::cout << (uint32_t)p[0] << " " << (uint32_t)p[1] << " " << (uint32_t)p[2] << " " << (uint32_t)p[3] << std::endl;
    //DEBUG
    
    return bit8;
}

std::ostream &operator<<( std::ostream &out, const Pixel& P )
{
    std::stringstream ss;

    ss << "Pixel:";
    ss << "[0]=" << std::setprecision(2) << P.f32[0];
    ss << "[1]=" << std::setprecision(2) << P.f32[1];
    ss << "[2]=" << std::setprecision(2) << P.f32[2];
    ss << "[3]=" << std::setprecision(2) << P.f32[3];

    out << ss.str();
    return out;
}


}
