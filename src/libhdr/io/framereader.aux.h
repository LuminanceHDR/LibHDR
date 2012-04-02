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

#ifndef LIBHDR_FRAMEREADER_AUX_H
#define LIBHDR_FRAMEREADER_AUX_H

//!
//! \file framereader.aux.h
//! \brief Auxiliary functions for the subscription of classes inherited from
//! FrameReader into the FrameReaderFactory
//!

#include "libhdr/template/objectfactory.h"
#include "libhdr/io/framereader.h"

namespace LibHDR
{
namespace IO
{

//! \brief Template function that subscribe the class Type to the FrameReaderFactory
template<typename Type>
bool subscribeFrameReaderFactory()
{
    bool status = true;
    // get pointer to FrameReaderFactory
    FrameReaderFactory::HoldType& factory = FrameReaderFactory::instance();

    // every class subscribed to FrameReaderFactory must expose this method
    std::vector<std::string> id_ = Type::getID();
    for (std::vector<std::string>::size_type idx = 0; idx < id_.size(); ++idx)
    {
        if ( !factory.subscribe(id_[idx], LibHDR::Template::createInstance<FrameReader, Type>) )
            status = false;
    }
    return status;
}

//! \brief C MACRO that calls correctly \c subscribeFrameReaderFactory()
#define REGISTER_FRAMEREADER(reader) \
    static bool factory_subscription##reader = subscribeFrameReaderFactory<reader>();

}
}

#endif // LIBHDR_FRAMEREADER_AUX
