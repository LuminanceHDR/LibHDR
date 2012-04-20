#ifndef LIBHDR_IO_EXR_IO_READ_HPP
#define LIBHDR_IO_EXR_IO_READ_HPP

//! \file exr_read.hpp
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \date 2012-04-20
//! \since 0.0.1

#include <libhdr/io/exr_tags.hpp>

#include <boost/gil/extension/io_new/detail/base.hpp>
#include <boost/gil/extension/io_new/detail/bit_operations.hpp>
#include <boost/gil/extension/io_new/detail/conversion_policies.hpp>
#include <boost/gil/extension/io_new/detail/row_buffer_helper.hpp>
#include <boost/gil/extension/io_new/detail/reader_base.hpp>
#include <boost/gil/extension/io_new/detail/io_device.hpp>
#include <boost/gil/extension/io_new/detail/typedefs.hpp>

namespace boost { namespace gil { namespace detail {

template< typename Device
          , typename ConversionPolicy
          >
class reader< Device
        , exr_tag
        , ConversionPolicy
        >
        : public reader_base< exr_tag
        , ConversionPolicy
        >
{
private:

    typedef typename ConversionPolicy::color_converter_type cc_t;

public:

    reader( Device& device )
        : _io_dev( device )
    {}

    reader( Device&     device
            , const cc_t& cc
            )
        : _io_dev( device )
        , reader_base< exr_tag
          , ConversionPolicy
          >( cc )
    {}

    image_read_info< exr_tag > get_info()
    {
        // your implementation here
    }

    template< typename View >
    void apply( const View& dst_view )
    {
        // your implementation here
    }
};

} // detail
} // gil
} // boost

#endif // LIBHDR_IO_EXR_IO_READ_HPP
