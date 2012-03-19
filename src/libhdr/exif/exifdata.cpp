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

#include "exifdata.h"

#include <exiv2/exiv2.hpp>
#include <cmath>
#include <iostream>

namespace LibHDR
{
namespace Exif
{

namespace
{
// reflected-light meter calibration constant
const float K = 12.07488f;
// default ISO value for camera that do not report io
const float DEFAULT_ISO = 100.f;
// invalid value
const float INVALID_VALUE = -1.f;
// invalid value
const float INVALID_EV_VALUE = -100000.f;
// default EVCOMP value
const float DEFAULT_EVCOMP = 0.0f;

float logBase(float value, float base)
{
   return (logf(value) / logf(base));
}

}

ExifData::ExifData()
{
    reset();
}

ExifData::ExifData(const std::string& filename)
{
    reset();
    fromFile(filename);
}

void ExifData::fromFile(const std::string& filename)
{
    reset();
    try
    {
        Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(filename);
        image->readMetadata();
        Exiv2::ExifData &exif_data = image->exifData();

        // if data is empty
        if (exif_data.empty()) return;

        // Exiv2 iterator in read-only
        Exiv2::ExifData::const_iterator it = exif_data.end();
        if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ExposureTime"))) != exif_data.end())
        {
            m_ExposureTime = it->toFloat();
        }
        else if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ShutterSpeedValue"))) != exif_data.end())
        {
            long num = 1;
            long div = 1;
            float tmp = expf(logf(2.0f) * it->toFloat());
            if (tmp > 1)
            {
                div = static_cast<long>(tmp + 0.5f);
            }
            else
            {
                num = static_cast<long>(1.0f/tmp + 0.5f);
            }
            m_ExposureTime = static_cast<float>(num)/div;
        }


        if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.FNumber"))) != exif_data.end())
        {
            m_F_Number = it->toFloat();
        }
        else if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ApertureValue"))) != exif_data.end())
        {
            m_F_Number = static_cast<float>(expf(logf(2.0f) * it->toFloat() / 2.f));
        }
        // some cameras/lens DO print the fnum but with value 0, and this is not allowed for ev computation purposes.
        if (m_F_Number == 0.0f)
        {
            m_F_Number = INVALID_VALUE;
        }

        //if iso is found use that value, otherwise assume a value of iso=100. (again, some cameras do not print iso in exif).
        if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ISOSpeedRatings"))) != exif_data.end())
        {
            m_IsoSpeed = it->toFloat();
        }

        if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ExposureBiasValue"))) != exif_data.end())
        {
            m_EvCompensation = it->toFloat();
        }
    }
    catch (Exiv2::AnyError& e)
    {
        return;
    }
}

const float& ExifData::exposureTime() const
{
    return m_ExposureTime;
}
bool ExifData::isExposureTime() const
{
    return (m_ExposureTime != INVALID_VALUE);
}
void ExifData::exposureTime(float et)
{
    m_ExposureTime = et;
}

const float& ExifData::isoSpeed() const
{
    return m_IsoSpeed;
}
bool ExifData::isIsoSpeed() const
{
    return true;
}
void ExifData::isoSpeed(float iso)
{
    m_IsoSpeed = iso;
}

const float& ExifData::fNumber() const
{
    return m_F_Number;
}
bool ExifData::isFNumber() const
{
    return (m_F_Number != INVALID_VALUE);
}
void ExifData::fNumber(float fnum)
{
    m_F_Number = fnum;
}

float ExifData::exposureValue() const
{
    if ( isFNumber() && isExposureTime() )
    {
        return logBase((m_F_Number*m_F_Number)/m_ExposureTime, 2.0f);
    }
    return INVALID_EV_VALUE;
}
bool ExifData::isExposureValue() const
{
    return (exposureValue() != INVALID_EV_VALUE);
}

const float& ExifData::exposureValueCompensation() const
{
    return m_EvCompensation;
}
bool ExifData::isExposureValueCompensation() const
{
    return (m_EvCompensation != 0.0f);
}
void ExifData::exposureValueCompensation(float evcomp)
{
    m_EvCompensation = evcomp;
}

float ExifData::getAverageSceneLuminance() const
{
    if ( isIsoSpeed() && isFNumber() && isExposureTime() )
    {
        return ( (m_ExposureTime * m_IsoSpeed) / (m_F_Number*m_F_Number*K) );
    }
    return INVALID_VALUE;
}

void ExifData::reset()
{
    // reset internal value
    m_ExposureTime = INVALID_VALUE;
    m_IsoSpeed = DEFAULT_ISO;
    m_F_Number = INVALID_VALUE;
    m_EvCompensation = DEFAULT_EVCOMP;
}

bool ExifData::isValid()
{
    return ( isIsoSpeed() && isFNumber() && isExposureTime() );
}

std::ostream& operator<<(std::ostream& out, const ExifData& exifdata)
{
    out << "Exposure value = " << exifdata.m_ExposureTime << ", ";
    out << "F value = " << exifdata.m_F_Number << ", ";
    out << "ISO = " << exifdata.m_IsoSpeed;

    return out;
}

}   // namespace Exif
}   // namespace LibHDR
