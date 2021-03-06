/*
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
 */
 
#ifndef LIBHDR_TAG
#define LIBHDR_TAG

#include <map>
#include <string>

namespace LibHDR
{

//! \brief TagContainer interface allows to read and modify tags. A tag is "name"="value" pair.
typedef std::map<std::string, std::string> TagContainer;
typedef std::pair<std::string, std::string> Tag;

//   /**
//    * Copy all tags from both the frame and its channels to the
//    * destination frame. If there is no corresponding destination
//    * channel for a source channel, the tags from that source channel
//    * will not be copied. Note, that all tags in the destination
//    * channel will be removed before copying. Therefore after this
//    * operation, the destination will contain exactly the same tags as
//    * the source.
//    */
    //void copyTags( Frame *from, Frame *to );

//   /**
//    * Copy all tags from one container into another. Note, that all
//    * tags in the destination channel will be removed before
//    * copying. Therefore after this operation, the destination will
//    * contain exactly the same tags as the source.
//    */
    //void copyTags( const TagContainer *from, TagContainer *to );

    //void writeTags( const TagContainer *tags, FILE *out );
    //void readTags( TagContainer *tags, FILE *in );

} // namespace LibHDR

#endif // LIBHDR_TAG

