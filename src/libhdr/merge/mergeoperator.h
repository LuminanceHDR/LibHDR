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

#ifndef LIBHDR_MERGEOPERATOR_H
#define LIBHDR_MERGEOPERATOR_H

#include <vector>
#include <string>

#include "libhdr_dlldefines.h"
#include "libhdr/image.h"
#include "libhdr/template/objectfactory.h"
#include "libhdr/template/singleton.h"
#include "libhdr/coreobject.h"
#include "libhdr/settings.h"
#include "libhdr/merge/mergeexceptions.h"

namespace LibHDR
{
namespace Merge
{
//! \class MergeOperator
//! \brief
class LIBHDR_API MergeOperator : public CoreObject
{
public:
    //! \brief ctor
    MergeOperator();

    //! \brief dtor
    virtual ~MergeOperator();

    //! \brief builds a new \c Image based on the merge operator asked
    //! to the \c MergeOperatorFactory
    //! \param[in] images initial set of images
    //! \param[in] settings settings for the merge operator
    //! \throw NoImagesException
    //! \throw MismatchImagesException
    ImagePtr merge(const std::vector<ImagePtr>& images, const Settings& settings = Settings());

protected:
    //! \brief core portion of the merge operator
    virtual void coreMerge(ImagePtr image, const std::vector<ImagePtr>& images, const Settings& settings = Settings()) = 0;
};

//! \brief Defines a Singleton holder for a factory of \c MergeOperator
typedef Template::Singleton< Template::ObjectFactory<MergeOperator, std::string> > MergeOperatorFactory;

}
}

#endif // MERGEOPERATOR
