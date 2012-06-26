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
/// \brief Output black-white point adjustment algorithm
/// \author Davide Anastasia <davideanastasia@users.sourceforge.net>
/// \date 2012-04-22
/// \since 0.0.1

#ifndef LIBHDR_COMPRESSOR_HPP
#define LIBHDR_COMPRESSOR_HPP

#include <boost/gil/gil_all.hpp>
#include <boost/gil/channel.hpp>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace libhdr
{

struct compressor_params
{
    compressor_params(float black_point = 0.0f,
                     float white_point = 1.0f)
        : black_point_(black_point),
          white_point_(white_point)
    {
        black_point_ = std::max(black_point_, 0.f);
        white_point_ = std::min(white_point_, 1.f);
    }

    inline
    const float& black_point() const
    {
        return black_point_;
    }

    inline
    const float& white_point() const
    {
        return white_point_;
    }

private:
    float black_point_;
    float white_point_;
};

template <typename C1, typename C2>
struct default_range_compressor_impl
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst,
                    const compressor_params& params) const
    {
        using namespace boost::gil;

        rgb32f_pixel_t rgb32f_pixel;                // create temporary pixel
        color_convert(src, rgb32f_pixel);           // fill temporary pixel

        float range = (params.white_point() - params.black_point());

        get_color(rgb32f_pixel, red_t()) =
                get_color(rgb32f_pixel, red_t())*range
                + params.black_point();
        get_color(rgb32f_pixel, green_t()) =
                get_color(rgb32f_pixel, green_t())*range
                + params.black_point();
        get_color(rgb32f_pixel, blue_t()) =
                get_color(rgb32f_pixel, blue_t())*range
                + params.black_point();

        color_convert(rgb32f_pixel, dst);           // fill final pixel
    }
};

template <>
struct default_range_compressor_impl<
        boost::gil::rgb_t,
        boost::gil::rgb_t
        >
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst,
                    const compressor_params& params) const
    {
        using namespace boost::gil;

        float range = (params.white_point() - params.black_point());

        get_color(dst, red_t()) =
                channel_convert<typename color_element_type<DstP, red_t>::type>(
                    static_cast<bits32f>(
                        channel_convert<bits32f>(
                            get_color(src, red_t())
                            ) * range
                        + params.black_point()
                        )
                    );

        get_color(dst, green_t()) =
                channel_convert<typename color_element_type<DstP, green_t>::type>(
                    static_cast<bits32f>(
                        channel_convert<bits32f>(
                            get_color(src, green_t())
                            ) * range
                        + params.black_point()
                        )
                    );

        get_color(dst, blue_t()) =
                channel_convert<typename color_element_type<DstP, blue_t>::type>(
                    static_cast<bits32f>(
                        channel_convert<bits32f>(
                            get_color(src, blue_t())
                            ) * range
                        + params.black_point()
                        )
                    );
    }
};

struct default_range_compressor
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst,
                    const compressor_params& params) const
    {
        using namespace boost::gil;

        typedef typename color_space_type<SrcP>::type SrcColorSpace;
        typedef typename color_space_type<DstP>::type DstColorSpace;
        default_range_compressor_impl<SrcColorSpace, DstColorSpace>()(src, dst, params);
    }
};

template <typename SrcP, typename DstP>
inline void range_compressor(const SrcP& src, DstP& dst,
                          const compressor_params& params)
{
    default_range_compressor()(src, dst, params);
}


}

#endif // LIBHDR_COMPRESSOR_HPP
