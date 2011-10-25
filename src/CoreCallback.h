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

#ifndef LIBHDR_CORECALLBACK
#define LIBHDR_CORECALLBACK

#include <list>
#include <string>

#include "DLLDefines.h"

namespace LibHDR
{

class LIBHDR_API CoreObject; // forward decleration

class LIBHDR_API CoreCallback
{
private:
    std::list<CoreObject*> m_Observed;
    bool m_Interrupt;

    void init();

public:
    CoreCallback();
    CoreCallback(CoreObject*);
    virtual ~CoreCallback();

    void registerCallback(CoreObject*);
    void unregisterCallback(CoreObject*);

    bool isTerminated();
    void setTerminated(bool);

    virtual void startCallback() = 0;
    virtual void stopCallback() = 0;

    virtual void setCallbackLength(int) = 0;
    virtual void setCallbackNextStep(int) = 0;

    virtual void setCallbackMessage(std::string) = 0;
};

inline bool CoreCallback::isTerminated()
{
    return m_Interrupt;
}

inline void CoreCallback::setTerminated(bool _b)
{
    m_Interrupt = _b;
}

} // end namespace LibHDR

#endif // LIBHDR_CORECALLBACK
