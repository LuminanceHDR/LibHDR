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
*  Heavily inspired by the original version of PFSTOOLS and its evolution in Luminance HDR
*/

#include <iostream>
#include <assert.h>
#if defined(_MSC_VER)
#include <malloc.h>
#else // I assume that, if it is not MSVC, it is GCC
#include <mm_malloc.h>
#endif

#include "array2d.h"

namespace LibHDR
{  
    
Array2D::Array2D( int cols, int rows ):
    m_Rows(rows),
    m_Cols(cols),
    m_Elems(rows*cols),
#if defined(_MSC_VER)
    // Aligned memory allocation allows faster vectorized access
    m_Data((float*)_aligned_malloc(m_Cols*m_Rows*sizeof(float), 16))
#else
    m_Data((float*)_mm_malloc(m_Cols*m_Rows*sizeof(float), 16))
#endif
{
    // check memory allocation
    if (m_Data == NULL) throw std::bad_alloc();
}

/*
Array2D::Array2D( int cols, int rows, float* data)
{
m_cols = cols;
m_rows = rows;
m_data = data;
m_is_data_owned = false;
}
*/

// copy constructor
Array2D::Array2D(const Array2D& rhs):
    m_Rows(rhs.m_Rows),
    m_Cols(rhs.m_Cols),
    m_Elems(rhs.m_Elems),
#if defined(_MSC_VER)
    m_Data((float*)_aligned_malloc(rhs.m_Elems*sizeof(float), 16))
#else
    m_Data((float*)_mm_malloc(rhs.m_Elems*sizeof(float), 16))
#endif
{
    if (m_Data == NULL) throw std::bad_alloc();

    memcpy(this->m_Data, rhs.m_Data, m_Elems*sizeof(float));
}

// Assignment operator
Array2D& Array2D::operator=(const Array2D& rhs)
{
    if (this == &rhs) return *this; // check self-assignment

#if defined(_MSC_VER)
    float* temp_pointer = (float*)_aligned_malloc(rhs.m_Elems*sizeof(float), 16);
#else
    float* temp_pointer = (float*)_mm_malloc(rhs.m_Elems*sizeof(float), 16);
#endif

    // Allocation failed, so I throw an exception
    if (temp_pointer == NULL) throw std::bad_alloc();

#if defined(_MSC_VER)
    _aligned_free(this->m_Data);
#else
    _mm_free(this->m_Data);
#endif

    this->m_Data = temp_pointer;
    /* Only after being sure the allocation is OK, I can update the data structure */
    this->m_Rows = rhs.m_Rows;
    this->m_Cols = rhs.m_Cols;
    this->m_Elems = rhs.m_Elems;

    memcpy(this->m_Data, rhs.m_Data, rhs.m_Elems*sizeof(float));

    return *this;
}

Array2D::~Array2D()
{
#if defined(_MSC_VER)
    _aligned_free(m_Data);
#else
    _mm_free(m_Data);
#endif
}

void Array2D::reset(const float value)
{
    //VEX_vset(this->m_data, value, this->m_rows*this->m_cols);
}

} // namespace LibHDR
