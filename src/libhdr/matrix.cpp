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
 */

#include "libhdr/matrix.h"

#include <pmmintrin.h>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

namespace LibHDR
{

template <typename Type>
class MatrixData
{
    // I leave everything in the public interface,
    // so I can access it easily in the definition of Matrix functions
public:
    int m_Rows;
    int m_Cols;
    int m_Elems;
    float* m_Data;

private:
    // hold the number of references for this instance
    // it must be set to zero during construction (or copy construction) of a new MatrixData
    int m_ReferenceCounter;
    boost::mutex m_Mutex;

public:
    // ctor
    MatrixData(int rows, int cols):
        m_Rows(rows),
        m_Cols(cols),
        m_Elems(rows*cols),
        m_Data( static_cast<float*>(_mm_malloc(rows*cols*sizeof(Type), 16)) ),
        m_ReferenceCounter(0)
    {
        //memset(m_Data, 0, rows*cols*sizeof(Type));
    }

    // copy ctor
    MatrixData(const MatrixData& other):
        m_Rows(other.m_Rows),
        m_Cols(other.m_Cols),
        m_Elems(other.m_Rows*other.m_Cols),
        m_Data( static_cast<float*>(_mm_malloc(other.m_Rows*other.m_Cols*sizeof(Type), 16)) ),
        m_ReferenceCounter(0)
    {
        memcpy(m_Data, other.m_Data, other.m_Rows*other.m_Cols*sizeof(Type));
    }

    // dtor
    ~MatrixData()
    {
        _mm_free(m_Data);
    }

public:
    inline void add_ref()
    {
        boost::mutex::scoped_lock l(m_Mutex);

        ++m_ReferenceCounter;
    }

    inline int release_ref()
    {
        boost::mutex::scoped_lock l(m_Mutex);

        return --m_ReferenceCounter;
    }

    inline int num_ref()
    {
        boost::mutex::scoped_lock l(m_Mutex);

        return m_ReferenceCounter;
    }
};

}

namespace boost
{
template <typename Type>
void intrusive_ptr_add_ref(LibHDR::MatrixData<Type> * p);

template <typename Type>
void intrusive_ptr_release(LibHDR::MatrixData<Type> * p);
}

namespace LibHDR
{

template<typename Type>
Matrix<Type>::Matrix(int rows, int cols):
    d( new MatrixData<Type>(rows, cols) )
{ }

template<typename Type>
Matrix<Type>::Matrix(const Matrix<Type> &other):
    d( other.d )
{}

template<typename Type>
Matrix<Type>::~Matrix()
{}

template<typename Type>
void Matrix<Type>::detach()
{
    if ( d->num_ref() > 1 )
    {
        // perform deep copy of the pointed element
        d.reset( new MatrixData<Type>(*d) );
    }
}


template<typename Type>
int Matrix<Type>::getRows() const
{
    return d->m_Rows;
}

template<typename Type>
int Matrix<Type>::getCols() const
{
    return d->m_Cols;
}

template<typename Type>
int Matrix<Type>::getElems() const
{
    return d->m_Elems;
}

template<typename Type>
Type& Matrix<Type>::operator()(int pos)
{
    detach();
    return ((Type*)d->m_Data)[ pos ];
}

template<typename Type>
const Type& Matrix<Type>::operator()(int pos) const
{
    return ((Type*)d->m_Data)[ pos ];
}

template<typename Type>
Type& Matrix<Type>::operator()(int row, int col)
{
    detach();
    return ((Type*)d->m_Data)[ row*d->m_Cols + col ];
}

template<typename Type>
const Type& Matrix<Type>::operator()(int row, int col) const
{
    return ((Type*)d->m_Data)[ row*d->m_Cols + col ];
}

template<typename Type>
float* Matrix<Type>::data()
{
    detach();
    return d->m_Data;
}

template<typename Type>
const float* Matrix<Type>::data() const
{
    return d->m_Data;
}

template<typename Type>
void Matrix<Type>::swap(Matrix<Type>& other)
{
    using std::swap;

    // Swap intrusive_ptr!
    d.swap(other.d);
}

template class Matrix<float>;
template class Matrix<Pixel>;

} // end namespace LibHDR

namespace boost
{

template <typename Type>
inline void intrusive_ptr_add_ref(LibHDR::MatrixData<Type> * p)
{
    p->add_ref();
}

template <typename Type>
inline void intrusive_ptr_release(LibHDR::MatrixData<Type> * p)
{
    if (p->release_ref() == 0)
        delete p;
}

} // namespace boost
