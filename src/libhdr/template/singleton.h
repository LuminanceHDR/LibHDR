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


//! \file singleton.h
//! \date 2012-02-05
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>

#ifndef LIBHDR_SINGLETON_H
#define LIBHDR_SINGLETON_H

#include <boost/utility.hpp>
#include <boost/thread.hpp>

namespace LibHDR
{
namespace Template
{
//! \class Creates a Singleton wrapper
//! \brief This class creates a Singleton wrapper around a class of type Type
//! (argument of the template). This class inherits boost::noncopyable: copy construction
//! and assignment are then disabled.
//! \param Type Specifies the type of the class that will be wrapped
template<typename Type>
class Singleton : public boost::noncopyable
{
public:
    typedef Type HoldType;

    //! \brief Create an instance of the wrapped type
    static Type& instance();

protected:
    //! \note the constructor is NOT public
    Singleton();

private:
    //! \brief The actual object
    static Type* m_instance;
//    static boost::mutex m_mutex;
};

template<typename Type>
Type* Singleton<Type>::m_instance = NULL;

//template<typename Type>
//boost::mutex Singleton<Type>::m_mutex;

template<typename Type>
Type& Singleton<Type>::instance()
{
    if (!m_instance)
    {
//        boost::unique_lock<boost::mutex> lock(m_mutex);
        if (!m_instance)
        {
            m_instance = new Type();
        }
    }
    return *m_instance;
}

}   // namespace Template
}   // namespace LibHDR

#endif // LIBHDR_SINGLETON_H


