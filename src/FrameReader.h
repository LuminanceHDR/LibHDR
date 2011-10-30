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

#ifndef LIBHDR_FRAMEREADER
#define LIBHDR_FRAMEREADER

#include <string>

#include "DLLDefines.h"
#include "CoreObject.h"
#include "Frame.h"

namespace LibHDR
{

namespace IO
{

enum InputFileFormat { PFS, TIFF, HDR, RGBE, EXR };

class LIBHDR_API IStrategyReader; // forward declaration

class LIBHDR_API FrameReader: public CoreObject
{
private:
    IStrategyReader* m_ReaderImpl;
    InputFileFormat m_FileFormat;
    void getFrameType(std::string);	// should be returning the frame type

public:
    FrameReader();
    FrameReader(std::string);
    ~FrameReader();

    void open(std::string);
    Frame* readFrame();
    void close();

    bool isOpen();
};

} // end namespace IO
} // end namespace LibHDR

#endif // LIBHDR_FRAMEREADER
