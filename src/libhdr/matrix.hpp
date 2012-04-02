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

#ifndef LIBHDR_MATRIX_HPP
#define LIBHDR_MATRIX_HPP

#include <libhdr/matrix.h>

#include <pmmintrin.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

namespace LibHDR
{
template <typename Type>
struct MatrixData
{
    // I leave everything in the public interface,
    // so I can access it easily in the definition of Matrix functions
    size_t m_Rows;
    size_t m_Cols;
    size_t m_Elems;
    Type* m_Data;

    // ctor
    MatrixData(size_t rows, size_t cols):
        m_Rows(rows),
        m_Cols(cols),
        m_Elems(rows*cols),
        m_Data( static_cast<Type*>(_mm_malloc(rows*cols*sizeof(Type), 16)) )
    {
        if ( m_Data == NULL )
            // _mm_malloc could not allocate the memory,
            // so I throw and exception
            throw std::bad_alloc();
    }

    // copy ctor
    MatrixData(const MatrixData& other):
        m_Rows(other.m_Rows),
        m_Cols(other.m_Cols),
        m_Elems(other.m_Rows*other.m_Cols),
        m_Data( static_cast<Type*>(
                    _mm_malloc(other.m_Rows*other.m_Cols*sizeof(Type), 16)) )
    {
        if ( m_Data == NULL )
            // _mm_malloc could not allocate the memory,
            // so I throw and exception
            throw std::bad_alloc();

        memmove(m_Data, other.m_Data, other.m_Rows*other.m_Cols*sizeof(Type));
    }

    // dtor
    ~MatrixData()
    {
        _mm_free(static_cast<void*>(m_Data));
    }
};

template<typename Type>
Matrix<Type>::Matrix(size_t rows, size_t cols):
    d( new MatrixData<Type>(rows, cols) )
{ }

template<typename Type>
Matrix<Type>::Matrix(const Matrix<Type> &other):
    d( other.d )
{}

template<typename Type>
Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type> &other)
{
    d = other.d;

    return *this;
}

template<typename Type>
Matrix<Type>::~Matrix()
{}

template<typename Type>
void Matrix<Type>::detach()
{
    if ( !d.unique() )
    {
        // perform deep copy of the pointed element
        d.reset( new MatrixData<Type>(*d) );
    }
}


template<typename Type>
size_t Matrix<Type>::getRows() const
{
    return d->m_Rows;
}

template<typename Type>
size_t Matrix<Type>::getCols() const
{
    return d->m_Cols;
}

template<typename Type>
size_t Matrix<Type>::getElems() const
{
    return d->m_Elems;
}

template<typename Type>
Type& Matrix<Type>::operator()(size_t pos)
{
    detach();
    return (d->m_Data)[ pos ];
}

template<typename Type>
const Type& Matrix<Type>::operator()(size_t pos) const
{
    return (d->m_Data)[ pos ];
}

template<typename Type>
Type& Matrix<Type>::operator()(size_t row, size_t col)
{
    detach();
    return (d->m_Data)[ row*d->m_Cols + col ];
}

template<typename Type>
const Type& Matrix<Type>::operator()(size_t row, size_t col) const
{
    return (d->m_Data)[ row*d->m_Cols + col ];
}

template<typename Type>
Type* Matrix<Type>::data()
{
    detach();
    return d->m_Data;
}

template<typename Type>
const Type* Matrix<Type>::data() const
{
    return d->m_Data;
}

template<typename Type>
const Type* Matrix<Type>::constData() const
{
    return d->m_Data;
}

template<typename Type>
void Matrix<Type>::swap(Matrix<Type>& other)
{
    using std::swap;

    // Swap shared_ptr!
    d.swap(other.d);
}


// iterator
template<typename Type>
typename Matrix<Type>::ConstIterator
Matrix<Type>::begin() const
{
    return typename
            Matrix<Type>::ConstIterator(d->m_Data);
}

template<typename Type>
typename Matrix<Type>::ConstIterator
Matrix<Type>::end() const
{
    return typename
            Matrix<Type>::ConstIterator(d->m_Data + d->m_Elems);
}

template<typename Type>
typename Matrix<Type>::Iterator
Matrix<Type>::begin()
{
    detach();
    return typename
            Matrix<Type>::Iterator(d->m_Data);
}

template<typename Type>
typename Matrix<Type>::Iterator
Matrix<Type>::end()
{
    detach();
    return typename
            Matrix<Type>::Iterator(d->m_Data + d->m_Elems);
}

// iterator
template<typename Type>
typename Matrix<Type>::ConstRowIterator
Matrix<Type>::rowBegin(size_t row) const
{
    return typename
            Matrix<Type>::ConstRowIterator(d->m_Data + row*d->m_Cols);
}

template<typename Type>
typename Matrix<Type>::ConstRowIterator
Matrix<Type>::rowEnd(size_t row) const
{
    return typename
            Matrix<Type>::ConstRowIterator(d->m_Data + (row + 1)*d->m_Cols);
}

template<typename Type>
typename Matrix<Type>::RowIterator
Matrix<Type>::rowBegin(size_t row)
{
    detach();
    return typename
            Matrix<Type>::Iterator(d->m_Data + row*d->m_Cols);
}

template<typename Type>
typename Matrix<Type>::RowIterator
Matrix<Type>::rowEnd(size_t row)
{
    detach();
    return typename
            Matrix<Type>::Iterator(d->m_Data + (row + 1)*d->m_Cols);
}

// iterator
template<typename Type>
typename Matrix<Type>::ConstColIterator
Matrix<Type>::colBegin(size_t col) const
{
    return typename
            Matrix<Type>::ConstColIterator(d->m_Data + col, d->m_Cols);
}

template<typename Type>
typename Matrix<Type>::ConstColIterator
Matrix<Type>::colEnd(size_t col) const
{
    return typename
            Matrix<Type>::ConstColIterator(d->m_Data + d->m_Elems + col, d->m_Cols);
}

template<typename Type>
typename Matrix<Type>::ColIterator
Matrix<Type>::colBegin(size_t col)
{
    detach();
    return typename
            Matrix<Type>::ColIterator(d->m_Data + col, d->m_Cols);
}

template<typename Type>
typename Matrix<Type>::ColIterator
Matrix<Type>::colEnd(size_t col)
{
    detach();
    return typename
            Matrix<Type>::ColIterator(d->m_Data + d->m_Elems + col, d->m_Cols);
}





} // end namespace LibHDR

#endif // LIBHDR_MATRIX_HPP
