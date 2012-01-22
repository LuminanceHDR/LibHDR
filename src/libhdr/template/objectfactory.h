/**
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
 *
 */

#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <map>

namespace LibHDR
{
namespace Template
{

//! \class ObjectFactory
//! \author Davide Anastasia
//! \since 0.0
//! \note Implementation inspired by http://www.artima.com/cppsource/subscription_problem.html
//! and the Loki library described in "Modern C++ Design" by Andrei Alexandrescu
template <typename AbstractProduct,
          typename IdentifierType,
          typename ProductCreator = AbstractProduct * (*)()>
class ObjectFactory
{
    //typedef ObjectFactory<AbstractProduct, IdentifierType, ProductCreator> ThisClass;
public:
    AbstractProduct * create(const IdentifierType & id)
    {
        typename Associations::const_iterator i = this->associations_.find(id);
        if (this->associations_.end() != i)
        {
            return (i->second)();
        }
        return NULL;
    }

    bool subscribe(const IdentifierType & id, ProductCreator creator)
    {
        return this->associations_.insert(Associations::value_type(id,
                                                                   creator)).second;
    }
    
private:
    typedef std::map<IdentifierType, ProductCreator> Associations;
    Associations associations_;
};

}
}

#endif
