/*
 * This file is a part of LibHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2012 Davide Anastasia
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
#include <sstream>

#include <libhdr/corecallback.h>
#include <libhdr/coreobject.h>
#include <libhdr/channel.h>
#include <libhdr/matrix.h>
#include <libhdr/io/framereader.h>

#include "test_utils.h"

using namespace LibHDR::IO;

int main(int argc, char *argv[])
{
    if ( !check_parameters(argc, argv) )
        return 1;

    switch (get_mode(argv[1]))
    {
    case 1:
    {
        FrameReaderFactory::HoldType& factory = FrameReaderFactory::instance();

        std::vector<std::string> subscribed = factory.getSubscribed();
        std::cout << "Subscribed types:\n";
        for (std::vector<std::string>::size_type idx = 0; idx < subscribed.size(); ++idx)
        {
            std::cout << subscribed[idx] << "\n";
        }
        return subscribed.size() == 0;
    }
    case 2:
    {
        boost::shared_ptr<FrameReader> reader( FrameReaderFactory::instance().create("pfs") );

        if ( reader.get() == 0)
            return 1;

        return 0;
    }
    }
    return 1;
}
