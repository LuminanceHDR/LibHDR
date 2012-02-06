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
 *  
 */

//! \file libhdr_version.h
//!
//! \brief Access to API's version information
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \date 2012-02-05
//! \since 0.0

#ifndef LIBHDR_VERSION_H
#define LIBHDR_VERSION_H

#include <string>

namespace LibHDR
{
//!
//! \class Version
//! \brief Access the version information for the API
//!
//! Using this class you can get the current version number as a string using
//! \c getVersion, or you can get major, minor, patch and build (derived from Git
//! hash) by calling \c getMajor, \c getMinor, \c getPatch and \c getBuild,
//! respectively.
//!
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \date 2012-02-05
//! \since 0.0
//! \note This class is heavily based on the similar class described in the book
//! "API design for C++" by Martin Reddy. Most of this library would be a mess without
//! this book. Or it would not exist at all
//!
class Version
{
public:
    //! \brief Return API major version number.
    //! \return The major version number as an integer.
    //! \since 0.0
    static int getMajor();

    //! \brief Return the API minor version number.
    //! \brief The minor version number as an integer
    //! \since 0.0
    static int getMinor();

    //! \brief Return the API patch version number.
    //! \brief The patch version number as an integer
    //! \since 0.0
    static int getPatch();

    //! \brief Return the API full version number
    //! \return The version string. e.g., "0.0.1"
    //! \since 0.0
    static std::string getVersion();

    //! \brief Return the API build version derived (if available from the Git hash)
    //! \return The build string, e.g., "aa00cc"
    //! \since 0.0
    static std::string getBuild();

    //! \brief Compare the current version number against a specific version.
    //! \param[in] major The major version number to compare against
    //! \param[in] minor The minor version number to compare against
    //! \param[in] patch The patch version number to compare against
    //! \return Retunrs true if specified version >= current version
    static bool isAtLeast(int major, int minor, int patch);
};

}
#endif /* LIBHDR_VERSION_H */
