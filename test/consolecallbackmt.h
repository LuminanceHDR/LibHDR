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
#include <boost/thread.hpp>

#include <libhdr/corecallback.h>

namespace LibHDRTest
{

const int PRINT_GRANULARITY = 1;

class ConsoleCallbackMT: public LibHDR::CoreCallback
{
private:
    static int sm_NumJobActive;

    int m_Duration;
    int m_CurrentStatus;
    int m_StatusLastPrint;

    boost::mutex m_StartStopMutex;
    boost::mutex m_UpdateMutex;

    void init()
    {
        m_Duration = 0;
        m_CurrentStatus = 0;
        m_StatusLastPrint = 0;
    }

public:
    ConsoleCallbackMT(): CoreCallback()
    {
        init();
    }
    ConsoleCallbackMT(LibHDR::CoreObject* _obj): CoreCallback(_obj)
    {
        init();
    }

    void startCallback()
    {
        boost::unique_lock<boost::mutex> lock(m_StartStopMutex);
        sm_NumJobActive++;

        if ( sm_NumJobActive == 1)
            std::cout << "Start Processing..." << std::endl;

    }

    void stopCallback()
    {
        boost::unique_lock<boost::mutex> lock(m_StartStopMutex);
        sm_NumJobActive--;

        if ( sm_NumJobActive == 0 )
        {
            if ( isTerminated() )
            {
                std::cout << "...abort! :-(" << std::endl;
            } else {
                std::cout << "...done!" << std::endl;
            }
            init(); // reset
        }
    }

    void setCallbackLength(int _duration)
    {
        boost::unique_lock<boost::mutex> lock(m_UpdateMutex);
        m_Duration += _duration;
    }

    void setCallbackNextStep(int _increment)
    {
        boost::unique_lock<boost::mutex> lock(m_UpdateMutex);
        m_CurrentStatus += _increment;

        if ( m_CurrentStatus >= (m_StatusLastPrint + PRINT_GRANULARITY) )
        {
            m_StatusLastPrint += PRINT_GRANULARITY;

            std::cout << "Step: " << m_CurrentStatus << "/" << m_Duration;
            std::cout << " (Jobs : " << sm_NumJobActive << ")" << std::endl;
        }
    }

    void setCallbackMessage(std::string&) {}
};

int ConsoleCallbackMT::sm_NumJobActive = 0;
} // namespace LibHDRTest

