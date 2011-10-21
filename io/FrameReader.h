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
 
#ifndef LIBHDR_FRAMEREADER
#define LIBHDR_FRAMEREADER

#include <string>

#include "core/CoreObject.h"
#include "io/IStrategyReader.h"

class FrameReader: public CoreObject
{
private:
	IStrategyReader* m_ReaderImpl;

	void getFrameType();	// should be returning the frame type

public:
	FrameReader();
	FrameReader(std::string _file_name);
	~FrameReader();

	void open(std::string);
	void readFrame(); // should be returning a Image*
	void close();

	bool isOpen();
};

#endif // LIBHDR_FRAMEREADER