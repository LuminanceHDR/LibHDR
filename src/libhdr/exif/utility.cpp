/*
 * This file is a part of LibHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2012 Davide Anastasia
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
 */

#include "utility.h"

#include <exiv2/exiv2.hpp>
#include <cmath>

namespace LibHDR
{
namespace Exif
{

NoExifDataException::NoExifDataException(const std::string& msg):
std::runtime_error(msg)
{}

float getSceneAverageLuminance(const std::string& filename)
{
    try
    {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty())
        {
            throw NoExifDataException("Exiv2: Empty EXIF Metadata");
        }

        Exiv2::ExifData::const_iterator it_expo = exifData.findKey(Exiv2::ExifKey("Exif.Photo.ExposureTime"));
        Exiv2::ExifData::const_iterator it_expo2 = exifData.findKey(Exiv2::ExifKey("Exif.Photo.ShutterSpeedValue"));
        Exiv2::ExifData::const_iterator it_iso  = exifData.findKey(Exiv2::ExifKey("Exif.Photo.ISOSpeedRatings"));
        Exiv2::ExifData::const_iterator it_fnum = exifData.findKey(Exiv2::ExifKey("Exif.Photo.FNumber"));
        Exiv2::ExifData::const_iterator it_fnum2 = exifData.findKey(Exiv2::ExifKey("Exif.Photo.ApertureValue"));

        float expo  = -1.f;
        if (it_expo != exifData.end())
        {
            expo = it_expo->toFloat();
        }
        else if (it_expo2 != exifData.end())
        {
            long num = 1;
            long div = 1;
            float tmp = expf(logf(2.0f) * it_expo2->toFloat());
            if (tmp > 1)
            {
                div = static_cast<long>(tmp + 0.5f);
            }
            else
            {
                num = static_cast<long>(1.0f/tmp + 0.5f);
            }
            expo = static_cast<float>(num)/div;
        }

        float fnum  = -1.f;
        if (it_fnum != exifData.end())
        {
            fnum = it_fnum->toFloat();
        }
        else if (it_fnum2 != exifData.end())
        {
            fnum = static_cast<float>(expf(logf(2.0f) * it_fnum2->toFloat() / 2.f));
        }
        // some cameras/lens DO print the fnum but with value 0, and this is not allowed for ev computation purposes.
        if (fnum == 0)
            return -1;

        //if iso is found use that value, otherwise assume a value of iso=100. (again, some cameras do not print iso in exif).
        float iso = -1.f;
        if (it_iso == exifData.end())
        {
            iso = 100.0;
        }
        else
        {
            iso = it_iso->toFloat();
        }

        //At this point the three variables have to be != -1
        if (expo!=-1 && iso!=-1 && fnum!=-1)
        {
            // 		std::cerr << "expo=" << expo << " fnum=" << fnum << " iso=" << iso << " |returned=" << (expo * iso) / (fnum*fnum*12.07488f) << std::endl;
            return ( (expo * iso) / (fnum*fnum*12.07488f) );
        }
        else
        {
            return -1;
        }
    }
    catch (Exiv2::AnyError& e)
    {
        return -1;
    }
}
}
}
