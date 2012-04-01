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

#include "weights.h"

#include <iostream>
#include <limits>
#include <cmath>

namespace LibHDR
{
namespace Merge
{
using namespace std;

namespace
{
const float triangular_min_trust_weight = 2.f/255.f;
const float triangular_max_trust_weight = 254.f/255.f;
const float triangluar_middle_trust_weight = triangular_min_trust_weight
        + (triangular_max_trust_weight - triangular_min_trust_weight)/2.f;
const float triangular_slope_weights = 2.f/(triangular_max_trust_weight - triangular_min_trust_weight);
}

WeightsTriangular::WeightsTriangular()
{
    using std::cout;
    using std::endl;

    cout << "WeightsTriangular {min: " << triangular_min_trust_weight << ", ";
    cout << "max: " << triangular_max_trust_weight << ", ";
    cout << "middle: " << triangluar_middle_trust_weight << ", ";
    cout << "slope: " << triangular_slope_weights << "}" << endl;
}


float WeightsTriangular::weight(float value)
{
    if (value < triangular_min_trust_weight) return 0.0f;
    if (value > triangular_max_trust_weight) return 0.0f;

    if ( value > triangluar_middle_trust_weight )
    {
        return -triangular_slope_weights*(value - triangular_max_trust_weight);
    }
    else
    {
        return triangular_slope_weights*(value - triangular_min_trust_weight);
    }
}

float WeightsTriangular::getMinimunTrustWeight()
{
    return triangular_min_trust_weight + std::numeric_limits<float>::epsilon();
}

float WeightsTriangular::getMaximumTrustWeight()
{
    return triangular_max_trust_weight - std::numeric_limits<float>::epsilon();
}

namespace
{
const float sin_min_trust_weight = 0.f;
const float sin_max_trust_weight = 1.0f;
const float sin_middle_trust_weight = 0.5f;
const float sin_pi = 4.0f * atanf(1.0f);
}

WeightsSin::WeightsSin()
{
    using std::cout;
    using std::endl;

    cout << "WeightsSin {min: " << sin_min_trust_weight << ", ";
    cout << "max: " << sin_max_trust_weight << ", ";
    cout << "middle: " << sin_middle_trust_weight << ", ";
    cout << "slope: 1/2*[sin(2*pi*x - pi/2) + 1] }" << endl;
}


float WeightsSin::weight(float value)
{
    if (value < sin_min_trust_weight) return 0.0f;
    if (value > sin_max_trust_weight) return 0.0f;

    return 0.5f * ( sinf(2*sin_pi*value - sin_pi/2.0f) + 1.0f );
}

float WeightsSin::getMinimunTrustWeight()
{
    return sin_min_trust_weight + std::numeric_limits<float>::epsilon();
}

float WeightsSin::getMaximumTrustWeight()
{
    return sin_max_trust_weight - std::numeric_limits<float>::epsilon();
}


}
}
