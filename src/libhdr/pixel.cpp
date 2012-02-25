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
#include <pmmintrin.h>

using namespace std;

//#if ((__GNUG__ > 4) && (__GNUCMINOR__ > 3))
//#define USE_OPTIMIZED_SSE
//#endif

namespace
{
static const __m128 C255F = _mm_set1_ps(255.f);
static const __m128 C0_5F = _mm_set1_ps(0.5f);

//#ifdef USE_OPTIMIZED_SSE
//// Floats constants
//static const __m128 C256_5F = _mm_set1_ps(256.5f);
//// Float to int masks
//static const __m128i CMaskF2I = _mm_set1_epi32(0x7FFFFF);
//// Integer constants
//static const __m128i C15I = _mm_set1_epi32(15);
//static const __m128i C16I = _mm_set1_epi32(16);
//static const __m128i C8I = _mm_set1_epi32(8);
//#endif
}

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
//#ifdef USE_OPTIMIZED_SSE
//    __m128 source __attribute__ ((aligned (16))) = vec4f;   // copy internal value

//    source = _mm_mul_ps(vec4f, C255F); // * 255
//    source = _mm_add_ps(source, C256_5F); // += (256 + 0.5);
//    __m128i* source_i = reinterpret_cast<__m128i*>(&source); // (*(*__m128i)&source)

//    *source_i = _mm_and_si128(*source_i, CMaskF2I);   // & 0x7FFFFF
//    *source_i = _mm_srl_epi32(*source_i, C15I); // >> 15

//    __m128i temp = _mm_shuffle_epi32(*source_i, _MM_SHUFFLE(3,2,3,2));
//    temp = _mm_sll_epi32(temp, C16I);
//    *source_i = _mm_add_epi32(*source_i, temp);

//    temp = _mm_shuffle_epi32(*source_i, _MM_SHUFFLE(0,1,0,1));
//    temp = _mm_sll_epi32(temp, C8I);
//    *source_i = _mm_add_epi32(*source_i, temp);

//    return reinterpret_cast<uint32_t*>(source_i)[0];
//#else
    __m128 pixel = _mm_mul_ps(vec4f, C255F);
    pixel = _mm_add_ps(pixel, C0_5F);

    // reuse of conv
    float* pix = reinterpret_cast<float*>(&pixel);
    uint8_t* s8 = reinterpret_cast<uint8_t*>(&pixel);
    uint32_t* s32 = reinterpret_cast<uint32_t*>(&pixel);

    s8[0] = static_cast<uint8_t>(pix[0]);
    s8[1] = static_cast<uint8_t>(pix[1]);
    s8[2] = static_cast<uint8_t>(pix[2]);
    s8[3] = static_cast<uint8_t>(pix[3]);

    return s32[0];
//#endif // USE_OPTIMIZED_SSE
}

ostream &operator<<( ostream &out, const Pixel& P )
{
    stringstream ss;

    ss << "Pixel:";
    ss << "[0]=" << std::setprecision(2) << P.f32[0];
    ss << "[1]=" << std::setprecision(2) << P.f32[1];
    ss << "[2]=" << std::setprecision(2) << P.f32[2];
    ss << "[3]=" << std::setprecision(2) << P.f32[3];

    out << ss.str();
    return out;
}


}
