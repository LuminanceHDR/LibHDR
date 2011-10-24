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

#include <iostream>
#include <boost/thread.hpp>

//#include <windows.h>

#include "CoreCallback.h"
#include "CoreObject.h"

#include "ConsoleCallbackMT.h"

class MockObject: public LibHDR::CoreObject
{
public:
    void run()
    {
        printf("DEBUG: run()\n");

        notifyStart();
        notifyJobLength(100);

        for (int i = 0; i < 100; i+=4)
        {
            notifyJobNextStep(4);
            if ( isTerminated() ) break;

            //Sleep( 500 );
        }
        notifyStop();
    }
};


int main()
{
    MockObject obj;
    ConsoleCallbackMT cb(&obj);

    MockObject obj2;
    cb.registerCallback(&obj2);

    boost::thread t1(boost::bind(&MockObject::run, &obj));

    //Sleep( 200 );

    boost::thread t2(boost::bind(&MockObject::run, &obj2));

    t1.join();
    t2.join();

    return 0;
}
