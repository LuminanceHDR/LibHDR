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
#include "Frame.h"
#include <list>

#define WIDTH 4000
#define HEIGTH 3000

int main()
{
    std::list<LibHDR::Frame> list_frames;

    LibHDR::Frame Ref(WIDTH, HEIGTH);
    list_frames.push_back(Ref);

    LibHDR::Channel* r = Ref.createChannel("R");
    float* r__ = r->getRawData();
    for (int idx = 0; idx < WIDTH*HEIGTH; idx++)
    {
        (*r)(idx) = 1.0f;
        //r__[idx] = 1.0f;
    }

    LibHDR::Channel* g = Ref.createChannel("G");
    float* g__ = g->getRawData();
    for (int idx = 0; idx < WIDTH*HEIGTH; idx++)
    {
        (*g)(idx) = 1.0f;
        //g__[idx] = 1.0f;
    }

    LibHDR::Channel* b = Ref.createChannel("B");
    float* b__ = b->getRawData();
    for (int idx = 0; idx < WIDTH*HEIGTH; idx++)
    {
        (*b)(idx) = 1.0f;
        //b__[idx] = 1.0f;
    }

    LibHDR::Frame Ref2 = Ref;
    list_frames.push_back(Ref2);

    for (int i=2; i; i--)
    {
        list_frames.push_back(LibHDR::Frame(Ref));
    }

    // for each frame I create 1 more channels:
    for (std::list<LibHDR::Frame>::iterator it = list_frames.begin();
         it != list_frames.end();
         it++)
    {
        LibHDR::Frame& frame = *it;

        LibHDR::Channel* r = frame.createChannel("A");
        float* r__ = r->getRawData();

        for (int idx = 0; idx < WIDTH*HEIGTH; idx++)
        {
            (*r)(idx) = 1.0f;
            //r__[idx] = 1.0f;
        }
    }

    return 0;
}
