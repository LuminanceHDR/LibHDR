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

#ifndef LIBHDR_MATRIX_H
#define LIBHDR_MATRIX_H

#include <boost/intrusive_ptr.hpp>

namespace LibHDR
{

// Forward declaration
template <typename Type>
class MatrixData;

//! \class Matrix
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
template <typename Type>
class Matrix
{
public:
    Matrix(int rows, int cols);
    virtual ~Matrix();

    Matrix(const Matrix<Type> &other);
    Matrix& operator=(const Matrix<Type>& rhs);

    void swap(Matrix<Type>& other);

    Type& operator()(int pos);
    const Type& operator()(int pos) const;

    Type& operator()(int row, int col);
    const Type& operator()(int row, int col) const;

    int getRows() const;
    int getCols() const;
    int getElems() const;

    float* data();
    const float* data() const;

protected:
    void detach();

private:
    boost::intrusive_ptr< MatrixData<Type> > d;
};

//template<typename In, typename Out>
//void copyMatrix(const Matrix<In>& mat_in, Matrix<Out>& mat_out)
//{
//    assert( mat_in.get_elems() == mat_out.get_elems() );

//    const In* in_elems = mat_in.data();
//    Out* out_elems = mat_out.data();

//    for (int idx = 0; idx < mat_in.get_elems(); ++idx)
//    {
//        out_elems[idx] = (Out)in_elems[idx];
//    }
//}

//template<typename T>
//std::ostream &operator<<( std::ostream &out, const Matrix<T>& M )
//{
//    using namespace std;
//    const std::streamsize _width = 7;

//    stringstream ss;

//    //ss.precision(3);
//    ss.fill(' ');
//    //ss.setf(ios::fixed);

//    ss << "[";
//    for (int i = 0; i < M.get_rows()-1; i++)
//    {
//        for (int j=0; j < M.get_cols()-1; j++)
//        {
//            ss << setw(_width) << M(i, j) << ",";
//        }
//        ss << setw(_width) << M(i, M.get_cols()-1) << ";";
//        ss << "\n";
//    }

//    for (int j=0; j < M.get_cols()-1; j++)
//    {
//        ss << setw(_width) << M(M.get_rows()-1, j) << ",";
//    }
//    ss << setw(_width) << M(M.get_rows()-1, M.get_cols()-1);
//    ss << "]" << endl;

//    out << ss.str();
//    return out;
//}

typedef Matrix<float> MatrixOfFloats;
typedef Matrix<float[4]> MatrixOfPixels;

} // end namespace LibHDR

#endif // MATRIX_H
