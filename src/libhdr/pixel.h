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

#ifndef LIBHDR_PIXEL
#define LIBHDR_PIXEL

#ifdef _WIN32
#define ALIGN_CLASS __declspec(align(16))
#else
#define ALIGN_CLASS
#endif

#include "libhdr_dlldefines.h"

#include <iostream>
#include <pmmintrin.h>

namespace LibHDR
{

class LIBHDR_API ALIGN_CLASS Pixel
{
public:
    union
    {
         float f32[4];
        __m128 vec4f;
    };

    explicit Pixel();
    explicit Pixel(float value);
    Pixel(float c0, float c1, float c2, float c3);
};

std::ostream &operator<<( std::ostream &out, const Pixel& P );

}

#endif // LIBHDR_PIXEL
