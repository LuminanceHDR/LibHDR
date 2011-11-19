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
#include <list>

#include <libhdr/frame.h>
#include <libhdr/rotate.h>

#define WIDTH 3000
#define HEIGTH 2000

int main()
{
    std::list<LibHDR::Frame> list_frames;

    LibHDR::Frame Ref(WIDTH, HEIGTH);
    list_frames.push_back(Ref);

    LibHDR::Channel& r = Ref.createChannel("R");
    for (int idx = 0; idx < WIDTH*HEIGTH; idx++)
    {
        r(idx) = 1.0f;
    }

    LibHDR::Channel& g = Ref.createChannel("G");
    for (int idx = 0; idx < WIDTH*HEIGTH; idx++)
    {
        g(idx) = 1.0f;
    }

    LibHDR::Channel& b = Ref.createChannel("B");
    for (int idx = 0; idx < WIDTH*HEIGTH; idx++)
    {
        b(idx) = 1.0f;
    }

    LibHDR::Frame Ref2 = Ref;
    list_frames.push_back(Ref2);

    for (int i=5; i; i--)
    {
        list_frames.push_back(LibHDR::Frame(Ref));
    }

    std::list<LibHDR::Frame*> rotated;
    // for each frame I create 1 more channels:
    for (std::list<LibHDR::Frame>::iterator it = list_frames.begin();
         it != list_frames.end();
         it++)
    {
        LibHDR::Frame& frame = *it;
        LibHDR::Channel& r = frame.createChannel("A");

        for (int idx = 0; idx < WIDTH*HEIGTH; idx++)
        {
            r(idx) = 1.0f;
        }

        rotated.push_back(LibHDR::getRotatedFrame(frame, LibHDR::CLOCKWISE));
    }

    for (std::list<LibHDR::Frame*>::iterator it = rotated.begin();
         it != rotated.end();
         it++)
    {
        delete (*it);
    }
    
    /*
     * This piece of code crash, because only Frame
     * is in charge of removing a Channel from its data structure
     *
     * To avoid this problem, Frame should return a reference to
     * a Channel, not a pointer
     *
     */
    
    /*
    LibHDR::Frame Ref(WIDTH, HEIGTH);
    LibHDR::Channel* ch = Ref.createChannel("X");
    
    delete ch;
     */
    
    
    return 0;
}
