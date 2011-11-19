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
 *  Original work by Rafal Mantiuk, <mantiuk@mpi-sb.mpg.de> for PFSTOOLS
 *
 */

#ifndef LIBHDR_ARRAY2D
#define LIBHDR_ARRAY2D

#include <cassert>

#include "libhdr_dlldefines.h"

namespace LibHDR
{ 
/**
 * @brief Two dimensional array of floats
 *
 * This class holds 2 dimensional arrays of floats in column-major order.
 * Allows easy indexing and retrieving array dimensions. It offers an undirect
 * access to the data (using (x)(y) or (elem) ) or a direct access to the data
 * (using getRawData()).
 * Subscript functions does not perform index checking.
 */
class LIBHDR_API Array2D
{
private:
    int m_Rows;
    int m_Cols;
    int m_Elems;
    float* m_Data;

public:
    explicit Array2D(int cols, int rows);
    //Array2D(int cols, int rows, float* data);

    Array2D& operator=(const Array2D& other);
    Array2D(const Array2D& other);

    /**
     * Each implementing class should provide its own destructor.
     * It must be virtual to allow derived class to call their destructor as well.
     */
    virtual ~Array2D();

    /**
      * Swap Array2D
      */
    void swap(Array2D&);

    /**
     * Access an element of the array for reading and
     * writing. Whether the given row and column are checked against
     * array bounds depends on an implementing class.
     *
     * Note, that if an Array2D object is passed as a pointer (what
     * is usually the case), to access its elements, you have to use
     * somewhat strange syntax: (*array)(row, column).
     *
     * @param cols number of a column (x) within the range [0,getCols()-1]
     * @param rows number of a row (y) within the range [0,getRows()-1]
     */
    float& operator()( int cols, int rows );

    /**
     * Access an element of the array for reading. Whether the given
     * row and column are checked against array bounds depends on an
     * implementing class.
     *
     * Note, that if an Array2D object is passed as a pointer (what
     * is usually the case), to access its elements, you have to use
     * somewhat strange syntax: (*array)(row, column).
     *
     * @param cols number of a column (x) within the range [0,getCols()-1]
     * @param rows number of a row (y) within the range [0,getRows()-1]
     */
    const float& operator()( int cols, int rows ) const;

    /**
     * Access an element of the array for reading and writing. This
     * is probably faster way of accessing elements than
     * operator(col, row). However there is no guarantee on the
     * order of elements as it usually depends on an implementing
     * class. The only assumption that can be make is that there are
     * exactly columns*rows elements and they are all unique.
     *
     * Whether the given index is checked against array bounds
     * depends on an implementing class.
     *
     * Note, that if an Array2D object is passed as a pointer (what
     * is usually the case), to access its elements, you have to use
     * somewhat strange syntax: (*array)(index).
     *
     * @param index index of an element within the range [0, getCols()*getRows()-1]
     */
    float& operator()( int index );

    /**
     * Access an element of the array for reading. This
     * is probably faster way of accessing elements than
     * operator(col, row). However there is no guarantee on the
     * order of elements as it usually depends on an implementing
     * class. The only assumption that can be make is that there are
     * exactly columns*rows elements and they are all unique.
     *
     * Whether the given index is checked against array bounds
     * depends on an implementing class.
     *
     * Note, that if an Array2D object is passed as a pointer (what
     * is usually the case), to access its elements, you have to use
     * somewhat strange syntax: (*array)(index).
     *
     * @param index index of an element within the range [0,getCols()*getRows()-1]
     */
    const float& operator()( int index ) const;

    /**
     * Get number of columns or, in case of an image, width.
     */
    int getCols() const;

    /**
     * Get number of rows or, in case of an image, height.
     */
    int getRows() const;

    /**
     * Direct access to the raw data
     */
    float* getRawData();

    /**
     * Direct access to the raw data
     */
    const float* getRawData() const;

    /**
     * Reset the entire vector data to the value "value"
     */
    void reset(const float value = 0.0f);
};

inline int Array2D::getCols() const
{
    return m_Cols;
}

inline int Array2D::getRows() const
{
    return m_Rows;
}

inline float* Array2D::getRawData()
{
    return m_Data;
}
inline const float* Array2D::getRawData() const
{
    return m_Data;
}

inline float& Array2D::operator()( int col, int row )
{
#ifdef _DEBUG
    assert( col >= 0 && col < m_Cols );
    assert( row >= 0 && row < m_Rows );
#endif
    return m_Data[ row*m_Cols + col ];
}

inline const float& Array2D::operator()( int col, int row ) const
{
#ifdef _DEBUG
    assert( col >= 0 && col < m_Cols );
    assert( row >= 0 && row < m_Rows );
#endif
    return m_Data[ row*m_Cols + col ];
}

inline float& Array2D::operator()( int index )
{
#ifdef _DEBUG
    assert( index >= 0 && index < m_Elems );
#endif
    return m_Data[index];
}

inline const float& Array2D::operator()( int index ) const
{
#ifdef _DEBUG
    assert( index >= 0 && index <= m_Elems );
#endif
    return m_Data[index];
}

void swap(Array2D& a, Array2D& b);

} // namespace LibHDR

//namespace std
//{
///*
// * Specialization of std::swap for Array2D
// */
//
//template<>
//void swap<LibHDR::Array2D>(LibHDR::Array2D& a, LibHDR::Array2D& b);
//
//} // namespace std

#endif // LIBHDR_ARRAY2D
