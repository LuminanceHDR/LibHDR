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

namespace LibHDR
{
namespace Merge
{

//! \brief Pure virtual base class for Weights
class Weights
{
public:
    Weights() {}
    virtual ~Weights() {}

    virtual float weight(float value) = 0;

    virtual float getMinimunTrustWeight() = 0;
    virtual float getMaximumTrustWeight() = 0;
};

// Triangular weights class
class WeightsTriangular : public Weights
{
public:
    WeightsTriangular();

    float weight(float value);

    float getMinimunTrustWeight();
    float getMaximumTrustWeight();
};

class WeightsSin : public Weights
{
public:
    WeightsSin();

    float weight(float value);

    float getMinimunTrustWeight();
    float getMaximumTrustWeight();
};

} // namespace Merge
} // namespace LibHDR


