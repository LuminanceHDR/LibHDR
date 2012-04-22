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

/// \file compressor.h
///
/// \brief Black-White point adjustment algorithm
/// \author Davide Anastasia <davideanastasia@users.sourceforge.net>
/// \date 2012-04-22
/// \since 0.0.1

#ifndef LIBHDR_COMPRESSOR_HPP
#define LIBHDR_COMPRESSOR_HPP

#include <boost/gil/gil_all.hpp>
#include <cmath>
#include <cassert>

namespace libhdr
{

struct compressor_params
{
    compressor_params(float black_point = 0.0f,
                     float white_point = 1.0f)
        : black_point_(black_point),
          white_point_(white_point)
    {
        // Todo: parameters check!
    }

    float black_point_;
    float white_point_;
};

template <typename Out>
struct compressor_channels
{
    compressor_channels(const compressor_params& params)
        : params_(params),
          compressor_factor_(1.f/(params.white_point_ -
                                  params.black_point_))
    {}

    template <typename T>
    Out operator()(const T& in)
    {
        return Out( (in - params_.black_point_)*compressor_factor_ );
    }
private:
    const compressor_params& params_;
    float compressor_factor_;
};

//
void compressor(const boost::gil::rgb32fc_view_t& src,
                const boost::gil::rgb32f_view_t& dst,
                const compressor_params& params)
{
    using namespace boost::gil;

    typedef channel_type<rgb32f_view_t>::type dst_channel_t;

    rgb32fc_view_t::iterator src_it = src.begin();
    for (rgb32f_view_t::iterator dst_it = dst.begin();
         dst_it != dst.end();
         ++dst_it, ++src_it)
    {
        static_transform(*src_it, *dst_it,
                         compressor_channels<dst_channel_t>(params));
    }
}


template <typename SrcView, typename DstView>
void compressor(const SrcView& src, const DstView& dst,
                const compressor_params& params)
{
    using namespace boost::gil;
/*
    gil_function_requires<ImageViewConcept<SrcView> >();
    gil_function_requires<MutableImageViewConcept<DstView> >();
    gil_function_requires<ColorSpacesCompatibleConcept<
            typename color_space_type<SrcView>::type,
            typename color_space_type<DstView>::type> >();
*/

    compressor(color_converted_view<rgb32fc_view_t>(src),
               color_converted_view<rgb32f_view_t>(dst),
               params);
}

}

#endif // LIBHDR_COMPRESSOR_HPP
