#ifndef LIBHDR_IO_EXR_TAGS_HPP
#define LIBHDR_IO_EXR_TAGS_HPP

//! \file exr_tags.hpp
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \date 2012-04-20
//! \since 0.0.1

#include <boost/gil/extension/io_new/detail/base.hpp>

namespace boost { namespace gil {

//! \brief define bmp tag
struct exr_tag : format_tag {};

//! \brief image_read_info for exr
template<>
struct image_read_info< exr_tag >
{};

//! \brief image_write_info for exr
template<>
struct image_write_info< exr_tag >
{};

} // gil
} // boost

#endif // LIBHDR_IO_EXR_TAGS_HPP
