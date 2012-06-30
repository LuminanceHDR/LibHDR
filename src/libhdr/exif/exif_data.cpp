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

#include <libhdr/exif/exif_data.hpp>

#include <exiv2/exiv2.hpp>
#include <cmath>
#include <iostream>

namespace LibHDR
{
namespace exif
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

float log_base(float value, float base)
{
   return (std::log(value) / std::log(base));
}

}

exif_data::exif_data()
{
    reset();
}

exif_data::exif_data(const std::string& filename)
{
    reset();
    from_file(filename);
}

void exif_data::from_file(const std::string& filename)
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
            exposure_time_ = it->toFloat();
        }
        else if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ShutterSpeedValue"))) != exif_data.end())
        {
            long num = 1;
            long div = 1;
            float tmp = std::exp(std::log(2.0f) * it->toFloat());
            if (tmp > 1)
            {
                div = static_cast<long>(tmp + 0.5f);
            }
            else
            {
                num = static_cast<long>(1.0f/tmp + 0.5f);
            }
            exposure_time_ = static_cast<float>(num)/div;
        }


        if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.FNumber"))) != exif_data.end())
        {
            f_number_ = it->toFloat();
        }
        else if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ApertureValue"))) != exif_data.end())
        {
            f_number_ = static_cast<float>(expf(logf(2.0f) * it->toFloat() / 2.f));
        }
        // some cameras/lens DO print the fnum but with value 0, and this is not allowed for ev computation purposes.
        if (f_number_ == 0.0f)
        {
            f_number_ = INVALID_VALUE;
        }

        //if iso is found use that value, otherwise assume a value of iso=100. (again, some cameras do not print iso in exif).
        if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ISOSpeedRatings"))) != exif_data.end())
        {
            iso_speed_ = it->toFloat();
        }

        if ((it = exif_data.findKey(Exiv2::ExifKey("Exif.Photo.ExposureBiasValue"))) != exif_data.end())
        {
            ev_compensation_ = it->toFloat();
        }
    }
    catch (Exiv2::AnyError& e)
    {
        return;
    }
}

const float& exif_data::exposure_time() const
{
    return exposure_time_;
}
bool exif_data::is_exposure_time() const
{
    return (exposure_time_ != INVALID_VALUE);
}
void exif_data::exposure_time(float et)
{
    exposure_time_ = et;
}

const float& exif_data::iso_speed() const
{
    return iso_speed_;
}
bool exif_data::is_iso_speed() const
{
    return true;
}
void exif_data::iso_speed(float iso)
{
    iso_speed_ = iso;
}

const float& exif_data::f_number() const
{
    return f_number_;
}
bool exif_data::is_f_number() const
{
    return (f_number_ != INVALID_VALUE);
}
void exif_data::f_number(float fnum)
{
    f_number_ = fnum;
}

float exif_data::exposure_value() const
{
    if ( is_f_number() && is_exposure_time() )
    {
        return log_base((f_number_*f_number_)/exposure_time_, 2.0f);
    }
    return INVALID_EV_VALUE;
}
bool exif_data::is_exposure_value() const
{
    return (exposure_value() != INVALID_EV_VALUE);
}

const float& exif_data::exposure_value_compensation() const
{
    return ev_compensation_;
}
bool exif_data::is_exposure_value_compensation() const
{
    return (ev_compensation_ != 0.0f);
}
void exif_data::exposure_value_compensation(float evcomp)
{
    ev_compensation_ = evcomp;
}

float exif_data::average_scene_luminance() const
{
    if ( is_iso_speed() && is_f_number() && is_exposure_time() )
    {
        return ( (exposure_time_ * iso_speed_) / (f_number_*f_number_*K) );
    }
    return INVALID_VALUE;
}

void exif_data::reset()
{
    // reset internal value
    exposure_time_ = INVALID_VALUE;
    iso_speed_ = DEFAULT_ISO;
    f_number_ = INVALID_VALUE;
    ev_compensation_ = DEFAULT_EVCOMP;
}

bool exif_data::is_valid() const
{
    return ( is_iso_speed() && is_f_number() && is_exposure_time() );
}

std::ostream& operator<<(std::ostream& out, const exif_data& exif_data)
{
    out << "Exposure time = " << exif_data.exposure_time_ << ", ";
    out << "F value = " << exif_data.f_number_ << ", ";
    out << "ISO = " << exif_data.iso_speed_ << ", ";
    out << "Exposure value = " << exif_data.exposure_value() << " (" << exif_data.ev_compensation_ << "), ";
    out << "Average Scene Luminance = " << exif_data.average_scene_luminance();

    return out;
}

}   // namespace exif
}   // namespace LibHDR
