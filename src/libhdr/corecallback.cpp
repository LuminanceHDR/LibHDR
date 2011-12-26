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

#include "libhdr/corecallback.h"
#include "libhdr/coreobject.h"

namespace LibHDR
{
using std::list;
using std::for_each;

CoreCallback::CoreCallback():
    m_Observed(NULL),
    m_Interrupt(false)
{}

CoreCallback::CoreCallback(CoreObject* co):
    m_Observed(NULL),
    m_Interrupt(false)
{
    registerCallback(co);
}

CoreCallback::~CoreCallback()
{
    if ( m_Observed != NULL )
        m_Observed->unsubscribe(this);
}

void CoreCallback::registerCallback(CoreObject* co)
{
    CoreObject* current_callback = m_Observed;

    // registering again the same callback?
    if ( co == current_callback ) return;

    // check if the CoreObject is NULL
    // if true, unsubscribe from current
    if ( !co ) unregisterCallback();

    // Am I registering the same CoreObject twice?
    //std::list<CoreObject*>::iterator it = std::find(m_Observed.begin(), m_Observed.end(), co);
    //if ( it != m_Observed.end() ) return;

    // Should be fine now
    m_Observed = co;
    co->subscribe(this);
}

void CoreCallback::unregisterCallback()
{
    if ( m_Observed != NULL )
        m_Observed->unsubscribe(this);

    m_Observed = NULL;
}

bool CoreCallback::isTerminated()
{
    return m_Interrupt;
}

void CoreCallback::setTerminated(bool b)
{
    m_Interrupt = b;
}

} // end namespace LibHDR
