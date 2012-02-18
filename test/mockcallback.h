/*
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
 */

#include <iostream>
#include <string>
#include <libhdr/corecallback.h>

namespace LibHDRTest
{

const int PRINT_GRANULARITY = 10;

class MockCallback: public LibHDR::CoreCallback
{
private:
    int m_Duration;
    int m_CurrentStatus;
    int m_StatusLastPrint;

public:
    MockCallback(): CoreCallback() {}
    MockCallback(LibHDR::CoreObject* _obj): CoreCallback(_obj) {}

    void startCallback()
    {
        std::cout << "Start Processing..." << std::endl;
        m_CurrentStatus = 0;
        m_StatusLastPrint = 0;
    }

    void stopCallback()
    {
        if ( isTerminated() )
        {
            std::cout << "...abort! :-(" << std::endl;
        } else {
            std::cout << "...done!" << std::endl;
        }
    }

    void setCallbackLength(int _duration)
    {
        m_Duration = _duration;
    }

    void setCallbackNextStep(int _increment)
    {
        m_CurrentStatus += _increment;

        if ( m_CurrentStatus >= (m_StatusLastPrint + PRINT_GRANULARITY) )
        {
            m_StatusLastPrint += PRINT_GRANULARITY;

            std::cout << "Step: " << m_CurrentStatus << "/" << m_Duration << std::endl;
        }
        // if ( m_CurrentStatus > 60 ) setTerminated(true);
    }

    void setCallbackMessage(const std::string&) {}
};
} // namespace LibHDRTest
