#ifndef LIBHDR_IO_EXR_IO_WRITE_HPP
#define LIBHDR_IO_EXR_IO_WRITE_HPP

//! \file exr_write.hpp
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \date 2012-04-20
//! \since 0.0.1

#include <libhdr/io/exr_tags.hpp>
#include <boost/gil/extension/io_new/detail/base.hpp>
#include <boost/gil/extension/io_new/detail/io_device.hpp>
#include <boost/gil/extension/io_new/detail/write_view.hpp>

namespace boost { namespace gil { namespace detail {

template< typename Device >
class writer< Device
        , exr_tag
        >
{
public:

    writer( Device & file )
        : _out( file )
    {}

    template<typename View>
    void apply( const View& view )
    {
        // your implementation here
    }

    template<typename View>
    void apply( const View&                        view
                , const image_write_info< exr_tag >& info )
    {
        // your implementation here
    }

private:

    Device& _out;
};

} // detail
} // gil
} // boost

#endif // LIBHDR_IO_EXR_IO_WRITE_HPP



