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

#include "libhdr/pixel.h"

#include <sstream>
#include <iomanip>

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
