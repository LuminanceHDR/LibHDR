/**
 * This file is a part of LibHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2011 Davide Anastasia
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * @author Davide Anastasia <davideanastasia@users.sourceforge.net>
 *
 */

#include <algorithm>
#include <functional>

#include "CoreCallback.h"
#include "CoreObject.h"

namespace LibHDR
{

using std::list;
using std::for_each;

void CoreCallback::init()
{
    m_Interrupt = false;
}

CoreCallback::CoreCallback()
{
    init();
}

CoreCallback::CoreCallback(CoreObject* _co)
{
    init();
    registerCallback(_co);
}

CoreCallback::~CoreCallback()
{
    if ( m_Observed.empty() ) return;
    // unsubscribe for_each of the
    for_each(m_Observed.begin(), m_Observed.end(), std::bind2nd( std::mem_fun( &CoreObject::unsubscribe ), this));
}

void CoreCallback::registerCallback(CoreObject* _co)
{
    /*
  * check if the CoreObject is NULL
  */
    if ( !_co ) return;

    /*
  * Am I registering the same CoreObject twice?
  */
    std::list<CoreObject*>::iterator it = std::find(m_Observed.begin(), m_Observed.end(), _co);

    if ( it != m_Observed.end() ) return;

    /*
  * Should be fine now
  */
    m_Observed.push_back(_co);
    _co->subscribe(this);
}

void CoreCallback::unregisterCallback(CoreObject* _co)
{
    if ( m_Observed.empty() ) return;

    m_Observed.remove(_co);
}

} // end namespace LibHDR
