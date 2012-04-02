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

#include <string>
#include <stdexcept>
#include <iosfwd>

#include "libhdr_dlldefines.h"

namespace LibHDR
{
//! \namespace Contains all the operations based on EXIF data
namespace Exif
{

//! \class ExifData
//! \brief Holds Exif Data
//!
class LIBHDR_API ExifData
{
public:
    //! \brief empty ctor
    ExifData();

    //! \param[in] filename Name of source file
    ExifData(const std::string& filename);

    //! \brief read exif data from file
    //! \param[in] filename Name of source file
    void fromFile(const std::string& filename);

    const float& exposureTime() const;
    bool isExposureTime() const;
    void exposureTime(float et);

    const float& isoSpeed() const;
    bool isIsoSpeed() const;
    void isoSpeed(float iso);

    const float& fNumber() const;
    bool isFNumber() const;
    void fNumber(float fnum);

    float exposureValue() const;
    bool isExposureValue() const;

    const float& exposureValueCompensation() const;
    bool isExposureValueCompensation() const;
    void exposureValueCompensation(float evcomp);

    //! \brief This function obtains the "average scene luminance" (cd/m^2) from an image file.
    //! "average scene luminance" is the L (aka B) value mentioned in [1]
    //! You have to take a log2f of the returned value to get an EV value.
    //!
    //! We are using K=12.07488f and the exif-implied value of N=1/3.125 (see [1]).
    //! K=12.07488f is the 1.0592f * 11.4f value in pfscalibration's pfshdrcalibrate.cpp file.
    //! Based on [3] we can say that the value can also be 12.5 or even 14.
    //! Another reference for APEX is [4] where N is 0.3, closer to the APEX specification of 2^(-7/4)=0.2973.
    //!
    //! [1] http://en.wikipedia.org/wiki/APEX_system
    //! [2] http://en.wikipedia.org/wiki/Exposure_value
    //! [3] http://en.wikipedia.org/wiki/Light_meter
    //! [4] http://doug.kerr.home.att.net/pumpkin/#APEX
    //!
    //! This function tries first to obtain the shutter speed from either of
    //! two exif tags (there is no standard between camera manifacturers):
    //! ExposureTime or ShutterSpeedValue.
    //! Same thing for f-number: it can be found in FNumber or in ApertureValue.
    //!
    //! F-number and shutter speed are mandatory in exif data for EV calculation, iso is not.
    //! \note This description is copied from the original source code in
    //! Luminance HDR http://qtpfsgui.sourceforge.net/
    float getAverageSceneLuminance() const;

    //! \brief reset Exif Data
    void reset();

    //! \brief returns whether enough information are available to compute additional values
    bool isValid() const;

    LIBHDR_API friend std::ostream& operator<<(std::ostream& out, const ExifData& exifdata);
private:
    float m_ExposureTime;
    float m_IsoSpeed;
    float m_F_Number;
    float m_EvCompensation;
};

LIBHDR_API std::ostream& operator<<(std::ostream& out, const ExifData& exifdata);

}
}
