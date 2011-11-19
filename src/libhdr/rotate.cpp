/**
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
 * 
 * @author Davide Anastasia <davideanastasia@users.sourceforge.net>
 *
 */

#include "rotate.h"

namespace LibHDR
{

    Frame* getRotatedFrame(const Frame& frame, RotationMode mode)
    { 
        int _width = frame.getWidth();
        int _height = frame.getHeight();

        // create frame with reversed dimensions
        Frame* _frame = new Frame(_height, _width); 

        for (ChannelList::const_iterator it = frame.getChannels().begin();
            it != frame.getChannels().end();
            it++)
        {
            Channel& _channel = _frame->createChannel((*it).getName());
            rotateArray2D((*it), _channel, mode);

            _channel.cloneTags((*it));
        }

        _frame->cloneTags(frame);

        return _frame;
    }

    void rotateArray2D(const Array2D& in, Array2D& out, RotationMode _mode)
    {
        // check dimension mismatch

        switch (_mode)
        {
        case CLOCKWISE:
            {
#pragma omp parallel for
                for (int j = 0; j < in.getRows(); j++)
                {
                    for (int i = 0; i < in.getCols(); i++)
                    {
                        out((i+1)*out.getCols() - 1 - j) = in(j *in.getCols() + i);
                    }
                }
                break;
            }
        case COUNTERCLOCKWISE:
            {
#pragma omp parallel for
                for (int j = 0; j < in.getRows(); j++)
                {
                    for (int i = 0; i < in.getCols(); i++)
                    {
                        out((in.getCols() - i - 1)*out.getCols() + j) = in(j*in.getCols() + i);
                    }
                }
            }
            break;
        }
    }

    void rotateFrame(Frame& _frame, RotationMode _mode)
    {
        Frame* _rotated = getRotatedFrame(_frame, _mode);
        _frame.swap(*_rotated);
    }

}
