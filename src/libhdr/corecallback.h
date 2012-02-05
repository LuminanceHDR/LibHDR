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

#ifndef LIBHDR_CORECALLBACK
#define LIBHDR_CORECALLBACK

#include <list>
#include <string>

#include "libhdr_dlldefines.h"

namespace LibHDR
{

class CoreObject; // forward decleration

//! \class CoreCallback
//! \brief Observes and receives notify from CoreObject objects.
//! \author Davide Anastasia <davideanastasia@gmail.com>
//! \since 0.0
class LIBHDR_API CoreCallback
{
public:
    CoreCallback();
    CoreCallback(CoreObject*);
    virtual ~CoreCallback();

    void registerCallback(CoreObject*);
    void unregisterCallback();

    bool isTerminated();
    void setTerminated(bool);

    virtual void startCallback() = 0;
    virtual void stopCallback() = 0;

    virtual void setCallbackLength(int) = 0;
    virtual void setCallbackNextStep(int) = 0;

    virtual void setCallbackMessage(std::string& message) = 0;

private:
    CoreObject* m_Observed;
    bool m_Interrupt;
};

} // end namespace LibHDR

#endif // LIBHDR_CORECALLBACK
