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

#ifndef LIBHDR_COREOBJECT
#define LIBHDR_COREOBJECT

#include <set>
#include <boost/utility.hpp>

#include "libhdr_dlldefines.h"


//! Library namespace
namespace LibHDR
{

class CoreCallback;


//! \class CoreObject
//! \brief CoreObject is the base class for all the operations that require a long computational time
//! and need to notify other object of their progress
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \since 0.0
class LIBHDR_API CoreObject : public boost::noncopyable
{
public:
    //! \brief CoreObject ctor
    CoreObject();

    //! \brief CoreObject ctor
    virtual ~CoreObject();

    //! \brief subscribe a new observer to CoreObject, notified every time a new event raises
    void subscribe(CoreCallback* cb);

    //! \brief unsubscribe current observer from CoreObject
    void unsubscribe(CoreCallback* cb);

    //! \brief notify all the observer of the start of a new operation
    void notifyStart();
    //! \brief notify all the observer the length of a new operation
    void notifyJobLength(int length);
    //! \brief notify all the observer that a certain number of increment have been completed
    //! \param[in] inc number of increments completed
    void notifyJobNextStep(int inc = 1);
    //! \brief notify all the observer that the operation has been fully completed
    void notifyStop();

    //! \brief send a message to all the observer
    void notifyMessage(const std::string& message);

    //! \brief check if one of the observer received a termination signal
    bool isTerminated();

    //! \brief disable notifications
    void disableNotify();

    //! \brief enable notifications
    void enableNotify();

    //! \brief turn on/off notifications
    //! \param[in] status status of the notifications: true for on, false for off
    void setNotify(bool status);

    //! \brief check if notifications are active
    bool isNotifyActive();

private:
    std::set<CoreCallback*> m_Callbacks;
    bool m_IsNotifyActive;
};

} // end namespace LibHDR

#endif // LIBHDR_COREOBJECT
