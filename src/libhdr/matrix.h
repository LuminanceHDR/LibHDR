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

#ifndef LIBHDR_MATRIX_H
#define LIBHDR_MATRIX_H

#include <iterator>
#include <boost/shared_ptr.hpp>
#include <libhdr/matrix_iterator.h>

namespace LibHDR
{

// Forward declaration
template <typename Type>
struct MatrixData;

//! \class Matrix
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
template <typename Type>
class Matrix
{
public:
    //! \brief constructor
    Matrix(size_t rows, size_t cols);

    //! \brief Virtual destructor.
    virtual ~Matrix();

    //! \brief copy constructor
    Matrix(const Matrix<Type> &other);
    //! \brief assignment operator
    Matrix& operator=(const Matrix<Type>& rhs);

    //! \brief Swap
    void swap(Matrix<Type>& other);

    Type& operator()(size_t pos);
    const Type& operator()(size_t pos) const;

    Type& operator()(size_t row, size_t col);
    const Type& operator()(size_t row, size_t col) const;

    //! \brief returns the number of rows of the current Matrix
    size_t getRows() const;
    //! \brief returns the number of cols of the current Matrix
    size_t getCols() const;
    //! \brief returns the number of elements of the current Matrix
    size_t getElems() const;

    //! \brief returns a pointer to the underlying buffer of data
    //! \note it performs a deep copy
    Type* data();
    //! \brief returns a pointer to the underlying buffer of data
    //! \note it does not perform a deep copy
    const Type* data() const;

    //! \brief returns a const pointer to the underlying buffer of data
    //! \note it never perform a deep copy
    const Type* constData() const;

protected:
    //! \brief Based on the number of references to the underlying data, performs a deep copy
    void detach();

private:
    boost::shared_ptr< MatrixData<Type> > d;

public:
    // iterator section
    typedef MatrixIterator<const Type> ConstIterator;
    typedef MatrixIterator<Type> Iterator;

    ConstIterator begin() const;
    ConstIterator end() const;

    Iterator begin();
    Iterator end();

    typedef MatrixIterator<const Type> ConstRowIterator;
    typedef MatrixIterator<Type> RowIterator;

    ConstRowIterator rowBegin(size_t row) const;
    ConstRowIterator rowEnd(size_t row) const;

    RowIterator rowBegin(size_t row);
    RowIterator rowEnd(size_t row);

    typedef MatrixIterator<const Type> ConstColIterator;
    typedef MatrixIterator<Type> ColIterator;

    ConstColIterator colBegin(size_t column) const;
    ConstColIterator colEnd(size_t column) const;

    ColIterator colBegin(size_t column);
    ColIterator colEnd(size_t column);
};

} // end namespace LibHDR

// Include template definition
#include <libhdr/matrix.hpp>

#endif // MATRIX_H
