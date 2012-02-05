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

#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

//! \file objectfactory.h
//! \date 2012-01-20
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>

#include <map>
#include <vector>

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
public:
    typedef ObjectFactory<AbstractProduct, IdentifierType, ProductCreator> ThisFactory;
    typedef std::map<IdentifierType, ProductCreator> Associations;

    //! \brief creates an instance of an object identified by id in the inheritance hierarchy of AbstractProduct
    AbstractProduct* create(const IdentifierType& id)
    {
        typename Associations::const_iterator i = this->m_associations.find(id);
        if (this->m_associations.end() != i)
        {
            return (i->second)();
        }
        return NULL;
    }

    bool subscribe(const IdentifierType& id, ProductCreator creator)
    {
        return this->m_associations.insert(typename Associations::value_type(id, creator)).second;
    }

    std::vector<IdentifierType> getSubscribed()
    {
        std::vector<IdentifierType> ids_;

        typename Associations::const_iterator it = this->m_associations.begin();
        typename Associations::const_iterator it_end = this->m_associations.end();
        for (; it != it_end; ++it)
        {
            ids_.push_back( it->first );
        }
        return ids_;
    }

private:
    Associations m_associations;
};

//! \brief Basic product creator for classes with empty default constructor
template <typename Base, typename Derived>
Base* createInstance()
{
    return new Derived;
}

}
}

#endif
