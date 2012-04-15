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

#ifndef LIBHDR_MATRIX_ITERATOR_HPP
#define LIBHDR_MATRIX_ITERATOR_HPP

#include <libhdr/matrix_iterator.h>
#include <cassert>

namespace LibHDR
{
template<typename Type>
MatrixIterator<Type>::MatrixIterator():
    p_(0),
    stride_(1)
{}

template<typename Type>
MatrixIterator<Type>::MatrixIterator(const MatrixIterator& r):
    p_(r.p_),
    stride_(r.stride_)
{}

template<typename Type>
MatrixIterator<Type>::MatrixIterator(typename MatrixIterator<Type>::pointer p,
                        typename MatrixIterator<Type>::difference_type stride):
    p_(p),
    stride_(stride)
{}

template<typename Type>
MatrixIterator<Type>& MatrixIterator<Type>::operator=(const MatrixIterator& r)
{
    p_ = r.p_;
    stride_ = r.stride_;
    return *this;
}

// prefix
template<typename Type>
MatrixIterator<Type>& MatrixIterator<Type>::operator++()
{
    assert(p_ != 0);

    p_ += stride_;
    return *this;
}

// prefix
template<typename Type>
MatrixIterator<Type>& MatrixIterator<Type>::operator--()
{
    assert(p_ != 0);

    p_ -= stride_;
    return *this;
}

// postfix
template<typename Type>
MatrixIterator<Type> MatrixIterator<Type>::operator++(int)
{
    assert(p_ != 0);

    return MatrixIterator(p_ += stride_);
}

// postfix
template<typename Type>
MatrixIterator<Type> MatrixIterator<Type>::operator--(int)
{
    assert(p_ != 0);

    return MatrixIterator(p_ -= stride_);
}

template<typename Type>
MatrixIterator<Type>
MatrixIterator<Type>::operator+(
        const typename MatrixIterator<Type>::difference_type& n) const
{
    assert(p_ != 0);

    return MatrixIterator(p_ + n*stride_);
}

template<typename Type>
MatrixIterator<Type>&
MatrixIterator<Type>::operator+=(
        const typename MatrixIterator<Type>::difference_type& n)
{
    assert(p_ != 0);

    p_ += n*stride_;
    return *this;
}

template<typename Type>
MatrixIterator<Type>
MatrixIterator<Type>::operator-(
        const typename MatrixIterator<Type>::difference_type& n) const
{
    assert(p_ != 0);

    return MatrixIterator(p_ - n*stride_);
}
template<typename Type>
MatrixIterator<Type>&
MatrixIterator<Type>::operator-=(
        const typename MatrixIterator<Type>::difference_type& n)
{
    assert(p_ != 0);

    p_ -= n*stride_;
    return *this;
}

template<typename Type>
typename MatrixIterator<Type>::reference
MatrixIterator<Type>::operator*() const
{
    assert(p_ != 0);

    return *p_;
}

template<typename Type>
typename MatrixIterator<Type>::pointer
MatrixIterator<Type>::operator->() const
{
    assert(p_ != 0);

    return p_;
}

template<typename Type>
typename MatrixIterator<Type>::reference
MatrixIterator<Type>::operator[](
        const typename MatrixIterator<Type>::difference_type& n) const
{
    assert(p_ != 0);

    return p_[n*stride_];
}

template<typename T>
bool
operator==(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2)
{
    return (r1.p_ == r2.p_);
}

template<typename T>
bool
operator!=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2)
{
    return (r1.p_ != r2.p_);
}

template<typename T>
bool
operator<(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2)
{
    return (r1.p_ < r2.p_);
}

template<typename T>
bool
operator>(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2)
{
    return (r1.p_ > r2.p_);
}

template<typename T>
bool
operator<=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2)
{
    return (r1.p_ <= r2.p_);
}

template<typename T>
bool
operator>=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2)
{
    return (r1.p_ >= r2.p_);
}

template<typename T>
typename MatrixIterator<T>::difference_type
operator+(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2)
{
    assert((r1.p_) != 0);
    assert((r2.p_) != 0);

    return r1.p_ + r2.p_;
}

template<typename T>
typename MatrixIterator<T>::difference_type
operator-(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2)
{
    assert((r1.p_) != 0);
    assert((r2.p_) != 0);

    return r1.p_ - r2.p_;
}
}

#endif // LIBHDR_MATRIX_ITERATOR_HPP
