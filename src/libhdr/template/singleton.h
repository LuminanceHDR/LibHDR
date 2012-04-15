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
#include <boost/thread/mutex.hpp>
#include <boost/circular_buffer.hpp>

namespace LibHDR
{
namespace Template
{
//! \class Singleton
//! \brief Creates a Singleton wrapper
//! This class creates a Singleton wrapper around a class of type Type
//! (argument of the template). This class inherits boost::noncopyable: copy construction
//! and assignment are then disabled.
//! \param Type Specifies the type of the class that will be wrapped
template<typename _Tp>
class Singleton : boost::noncopyable
{
public:
    typedef _Tp HoldType;

    //! \brief Create an instance of the wrapped type
    static _Tp& instance();

protected:
    //! \note the constructor is NOT public
    Singleton();

private:
    //! \brief The actual object
    static _Tp* instance_;
#ifdef WIN32
    static boost::mutex mutex_;
#endif
};

template<typename _Tp>
_Tp* Singleton<_Tp>::instance_ = NULL;

#ifdef WIN32
template<typename _Tp>
boost::mutex Singleton<_Tp>::mutex_;
#endif

template<typename _Tp>
_Tp& Singleton<_Tp>::instance()
{
    if (!instance_)
    {
#ifdef WIN32
        boost::unique_lock<boost::mutex> lock(mutex_);
#endif
        if (!instance_)
        {
            instance_ = new _Tp();
        }
    }
    return *instance_;
}

}   // namespace Template
}   // namespace LibHDR

#endif // LIBHDR_SINGLETON_H


