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

#include <algorithm>
#include <functional>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include "libhdr/coreobject.h"
#include "libhdr/corecallback.h"

namespace LibHDR
{
    
using namespace boost::lambda;
using std::for_each;

CoreObject::CoreObject():
    m_IsNotifyActive(true)
{}

CoreObject::~CoreObject()
{
    /*
     * In the dstr there is no check of the m_IsNotifyActive because
     * we want in anycase to notify all the observers!
     */

    /* unset all the observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), bind(&CoreCallback::unregisterCallback, _1));
}

void CoreObject::subscribe(CoreCallback* _cb)
{
    m_Callbacks.push_back(_cb);
}

void CoreObject::unsubscribe(CoreCallback* _cb)
{
    m_Callbacks.remove(_cb);
}

void CoreObject::notifyStart()
{
    if ( !m_IsNotifyActive ) return;
    /* update all observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), bind( &CoreCallback::startCallback, _1));
}

void CoreObject::notifyJobLength(int _i)
{
    if ( !m_IsNotifyActive ) return;
    /* update all observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), bind( &CoreCallback::setCallbackLength, _1, _i));
}

void CoreObject::notifyJobNextStep(int _inc)
{
    if ( !m_IsNotifyActive ) return;
    /* update all observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), bind( &CoreCallback::setCallbackNextStep, _1, _inc));
}

void CoreObject::notifyStop()
{
    if ( !m_IsNotifyActive ) return;
    /* update all observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), bind( &CoreCallback::stopCallback, _1));
}

void CoreObject::notifyMessage(const std::string& /*message*/)
{
    // TODO: to implement
    if ( !m_IsNotifyActive ) return;
}

bool CoreObject::isTerminated()
{
    /* look for an callback with the termination status active */
    std::list<CoreCallback*>::iterator it = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), bind( &CoreCallback::isTerminated, _1) == true);

    return ( it != m_Callbacks.end() ) ? true : false;
}

void CoreObject::disableNotify()
{
    m_IsNotifyActive = false;
}

void CoreObject::enableNotify()
{
    m_IsNotifyActive = true;
}

void CoreObject::setNotify(bool status)
{
    m_IsNotifyActive = status;
}

bool CoreObject::isNotifyActive()
{
    return m_IsNotifyActive;
}

} // end namespace LibHDR
