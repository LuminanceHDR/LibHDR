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

#ifndef LIBHDR_ISTRATEGYREADER
#define LIBHDR_ISTRATEGYREADER

#include <string>

namespace LibHDR
{

namespace IO
{

class FrameReader; // forward declaration

class IStrategyReader
{
private:
    const FrameReader& m_FrameReader;

    enum {OPEN, CLOSE} m_Status;

    void setOpen(bool);
public:
    IStrategyReader(const FrameReader&); // cstr
    ~IStrategyReader();

    virtual void open(std::string) = 0;
    virtual void readFrame() = 0;
    virtual void close() = 0;

    bool isOpen();
};

} // end namespace IO
} // end namespace LibHDR

#endif // LIBHDR_ISTRATEGYREADER
