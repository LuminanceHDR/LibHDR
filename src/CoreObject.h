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

#ifndef LIBHDR_COREOBJECT
#define LIBHDR_COREOBJECT

#include <list>

#include "DLLDefines.h"

class CoreCallback;

class LIBHDR_API CoreObject
{
public:
    CoreObject(): m_IsNotifyActive(true) {}
    virtual ~CoreObject();

    void subscribe(CoreCallback*);
    void unsubscribe(CoreCallback*);

    void notifyStart();
    void notifyJobLength(int);
    void notifyJobNextStep(int inc = 1); // Thanks, Steve!
    void notifyStop();
    void notifyMessage();

    bool isTerminated();

    void disableNotify();
    void enableNotify();
    void setNotify(bool);
    bool isNotifyActive();

private:
    std::list<CoreCallback*> m_Callbacks;
    bool m_IsNotifyActive;
};

inline void CoreObject::disableNotify()
{
    m_IsNotifyActive = false;
}

inline void CoreObject::enableNotify()
{
    m_IsNotifyActive = true;
}

inline void CoreObject::setNotify(bool _b)
{
    m_IsNotifyActive = _b;
}

inline bool CoreObject::isNotifyActive()
{
    return m_IsNotifyActive;
}

#endif // LIBHDR_COREOBJECT
