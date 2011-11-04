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
 */

#include "Tag.h"

#include <list>
#include <stdio.h>
#include <string>

using namespace std;

namespace LibHDR
{
    /*
    void copyTags( Frame *from, Frame *to )
    {
        copyTags( from->getTags(), to->getTags() );
        pfs::ChannelIterator *it = from->getChannels();
        while ( it->hasNext() )
        {
            pfs::Channel *fromCh = it->getNext();
            pfs::Channel *toCh = to->getChannel( fromCh->getName() );
            if ( toCh == NULL ) // Skip if there is no corresponding channel
                continue;
            copyTags( fromCh->getTags(), toCh->getTags() );
        }

    }

    void copyTags( const TagContainer *f, TagContainer *t )
    {
        t->removeAllTags();

        for ( TagList::const_iterator it = f->tagsBegin(); it != f->tagsEnd(); it++ )
        {
            t->appendTag( *it );
        }
    }

    void readTags( TagContainer *tags, FILE *in )
    {
        int readItems;
        int tagCount;
        readItems = fscanf( in, "%d" PFSEOL, &tagCount );
        if ( readItems != 1 || tagCount < 0 || tagCount > 1024 )
        {
            throw Exception( "Corrupted PFS tag section: missing or wrong number of tags" );
        }

        char buf[MAX_TAG_STRING+1];
        for( int i = 0; i < tagCount; i++ )
        {
            char *read = fgets( buf, MAX_TAG_STRING, in );
            if( read == NULL ) throw Exception( "Corrupted PFS tag section: missing tag" );
            char *equalSign = strstr( buf, "=" );
            if( equalSign == NULL ) throw Exception( "Corrupted PFS tag section ('=' sign missing)" );
            tags->appendTagEOL( buf );
        }
    }

    void writeTags( const TagContainer *tags, FILE *out )
    {
        fprintf( out, "%d" PFSEOL, tags->getSize() );
        for (TagList::const_iterator it = tags->tagsBegin(); it != tags->tagsEnd(); it++ )
        {
            fprintf( out, "%s", it->c_str() );
            fprintf( out, PFSEOL );
        }
    }
    */

} // namespace LibHDR




