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

#ifndef LIBHDR_AUTO_DELETER_H
#define LIBHDR_AUTO_DELETER_H

#include <stdio.h>

namespace LibHDR
{
namespace details
{

//! \brief Traits cass for \c ResourceHandler
template<typename T>
struct ResourceHandlerTraits
{
    static
    void release(T*)
    {}
};

//! \brief Specialization of \c ResourceHandlerTraits for stdio.h FILE
template<>
struct ResourceHandlerTraits<FILE>
{
    static
    void release(FILE* p)
    {
        fclose(p);
    }
};


//! \brief auto_deleter for shared resources allocated on the heap
//! \note to customize the behaviour of your \c ResourceHandler, you must
//! specialize the \c ResourceHandlerTraits class
template<typename T, typename Traits = ResourceHandlerTraits<T> >
class ResourceHandler
{
public:
    ResourceHandler():
        p_(NULL)
    {}

    ResourceHandler(T* p):
        p_(p)
    {}

    void reset(T* p = NULL)
    {
        if (p_ != NULL)
        {
            Traits::release(p_);
        }
        p_ = p;
    }

    ~ResourceHandler()
    {
        if (p_ != NULL)
        {
            Traits::release(p_);
        }
    }

    inline
    T* get()
    {
        return p_;
    }

private:
    T* p_;
};

}
}


#endif // LIBHDR_AUTO_DELETER_H
