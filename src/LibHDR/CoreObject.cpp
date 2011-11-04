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
 * @author Davide Anastasia <davideanastasia@users.sourceforge.net>
 *
 */

#include <algorithm>
#include <functional>

#include "CoreObject.h" 
#include "CoreCallback.h"

namespace LibHDR
{

using std::for_each;
using std::bind2nd;
using std::mem_fun;

/*
 * cstr is defined inline in the class definition
 *
 *
 * CoreObject::CoreObject() { }
 */

CoreObject::~CoreObject()
{
    /*
     * In the dstr there is no check of the m_IsNotifyActive because
     * we want in anycase to notify all the observed!
     */

    /* unset all the observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), bind2nd( mem_fun( &CoreCallback::unregisterCallback ), this));
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
    for_each(m_Callbacks.begin(), m_Callbacks.end(), mem_fun( &CoreCallback::startCallback ));
}

void CoreObject::notifyJobLength(int _i)
{
    if ( !m_IsNotifyActive ) return;
    /* update all observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), bind2nd( mem_fun( &CoreCallback::setCallbackLength ), _i));
}

void CoreObject::notifyJobNextStep(int _inc)
{
    if ( !m_IsNotifyActive ) return;
    /* update all observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), bind2nd( mem_fun( &CoreCallback::setCallbackNextStep ), _inc));
}

void CoreObject::notifyStop()
{
    if ( !m_IsNotifyActive ) return;
    /* update all observers */
    for_each(m_Callbacks.begin(), m_Callbacks.end(), mem_fun( &CoreCallback::stopCallback ));
}

bool CoreObject::isTerminated()
{
    /* look for an callback with the termination status active */
    std::list<CoreCallback*>::iterator it = std::find_if (m_Callbacks.begin(), m_Callbacks.end(), mem_fun( &CoreCallback::isTerminated ));

    return ( it != m_Callbacks.end() ) ? true : false;
}

} // end namespace LibHDR
