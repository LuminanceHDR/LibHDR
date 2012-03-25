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

#ifndef LIBHDR_DEBEVEC97_H
#define LIBHDR_DEBEVEC97_H

#include <vector>
#include <string>

#include "libhdr_dlldefines.h"
#include "libhdr/merge/mergeoperator.h"

namespace LibHDR
{
namespace Merge
{
struct Debevec97Impl;

class LIBHDR_API Debevec97 : public MergeOperator
{
public:
    Debevec97();

    virtual ~Debevec97();

protected:
    //! \brief core portion of the Debevec97 merge operator
    //! \pre image.getWidth() == images[i].getWidth() for all i
    //! \pre image.getHeight() == images[i].getHeight() for all i
    //! \post
    virtual void coreMerge(ImagePtr image, const std::vector<ImagePtr>& images, const Settings& settings);

private:
    boost::shared_ptr<Debevec97Impl> m_impl;
};


}
}

#endif // #ifndef LIBHDR_DEBEVEC97_H
