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

#ifndef LIBHDR_MATRIX_ITERATOR_H
#define LIBHDR_MATRIX_ITERATOR_H

#include <iterator>

namespace LibHDR
{
// forward declaration
template<typename Type>
class Matrix;

//! \brief Iterator for the class Matrix
//! This class is inspired from the cited webpage. However, it is a generic
//! iterator for the class \c Matrix, that also allows to
//! \ref http://zotu.blogspot.co.uk/2010/01/creating-random-access-iterator.html
template<typename Type>
class MatrixIterator :
        public std::iterator<std::random_access_iterator_tag, Type>
{
private:
    // grant friendship to the contanier class, so it can
    friend class Matrix<Type>;

    //! \brief Private constructor for the iterator class
    //! this constructor can be used from
    MatrixIterator(typename MatrixIterator<Type>::pointer p,
                   typename MatrixIterator<Type>::difference_type stride = 1);

public:
    // default ctor
    //! \brief empty default ctor for \c MatrixIterator
    MatrixIterator();
    //! \brief Copy constructor
    MatrixIterator(const MatrixIterator& r);

    inline
    typename MatrixIterator<Type>::difference_type getStride() const
    {
        return stride_;
    }

    template<typename T2>
    MatrixIterator(const MatrixIterator<T2>& r):
        p_(&(*r)),
        stride_(r.getStride())
    {}

    template<typename T2>
    MatrixIterator& operator=(const MatrixIterator<T2>& r)
    {
        p_ = &(*r);
        stride_ = r.getStride();
        return *this;
    }

    //! \brief Assignment operator
    inline
    MatrixIterator& operator=(const MatrixIterator& r);
    // prefix
    inline
    MatrixIterator& operator++();
    // prefix
    inline
    MatrixIterator& operator--();
    // postfix
    inline
    MatrixIterator operator++(int);
    // postfix
    inline
    MatrixIterator operator--(int);

    inline
    MatrixIterator operator+(
            const typename MatrixIterator<Type>::difference_type& n) const;
    inline
    MatrixIterator& operator+=(
            const typename MatrixIterator<Type>::difference_type& n);

    inline
    MatrixIterator operator-(
            const typename MatrixIterator<Type>::difference_type& n) const;
    inline
    MatrixIterator& operator-=(
            const typename MatrixIterator<Type>::difference_type& n);

    inline
    typename MatrixIterator<Type>::reference
    operator*() const;

    inline
    typename MatrixIterator<Type>::pointer
    operator->() const;

    inline
    typename MatrixIterator<Type>::reference
    operator[](const typename MatrixIterator<Type>::difference_type& n) const;

    template<typename T>
    friend bool
    operator==(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

    template<typename T>
    friend bool
    operator!=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

    template<typename T>
    friend bool
    operator<(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

    template<typename T>
    friend bool
    operator>(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

    template<typename T>
    friend bool
    operator<=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

    template<typename T>
    friend bool
    operator>=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

    template<typename T>
    friend typename MatrixIterator<T>::difference_type
    operator+(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

    template<typename T>
    friend typename MatrixIterator<T>::difference_type
    operator-(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

protected:
    typename MatrixIterator<Type>::pointer p_;
    typename MatrixIterator<Type>::difference_type stride_;
};

template<typename T>
bool
operator==(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

template<typename T>
bool
operator!=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

template<typename T>
bool
operator<(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

template<typename T>
bool
operator>(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

template<typename T>
bool
operator<=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

template<typename T>
bool
operator>=(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

template<typename T>
typename MatrixIterator<T>::difference_type
operator+(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

template<typename T>
typename MatrixIterator<T>::difference_type
operator-(const MatrixIterator<T>& r1, const MatrixIterator<T>& r2);

}

#include <libhdr/matrix_iterator.hpp>

#endif // LIBHDR_MATRIX_ITERATOR_H
