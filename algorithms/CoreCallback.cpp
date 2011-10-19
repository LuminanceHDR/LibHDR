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

#include "CoreCallback.h"
#include "CoreObject.h"

void CoreCallback::init()
{
    m_Observed = NULL;
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
    if ( !m_Observed ) return;
    m_Observed->unsubscribe(this);
}

void CoreCallback::registerCallback(CoreObject* _co)
{
    /*
  * Am I registering to the same CoreObject?
  */
    if ( _co == m_Observed ) return;

    /*
  * check if I am already observing somebody
  * If that is the case, unregister first and subscribe to the new one later
  */
    if ( m_Observed ) m_Observed->unsubscribe(this);

    m_Observed = _co;
    if ( m_Observed ) m_Observed->subscribe(this);
}

void CoreCallback::unregisterCallback()
{
    if ( !m_Observed ) return;
    m_Observed->unsubscribe(this);
    m_Observed = NULL;
}
