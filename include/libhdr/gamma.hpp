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

//! \file gamma.hpp
//!
//! \brief Gamma adjustment algorithm
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \date 2012-06-25
//! \since 0.0.1

#ifndef LIBHDR_GAMMA_HPP
#define LIBHDR_GAMMA_HPP

#include <boost/gil/gil_all.hpp>
#include <cmath>

namespace libhdr
{

/*

template <typename C1, typename C2>
struct default_gamma_converter_impl
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst, float gamma) const
    {
        using namespace boost::gil;

        rgb32f_pixel_t rgb32f_pixel;                // create temporary pixel
        gray32f_pixel_t gray_pixel;
        color_convert(src, rgb32f_pixel);           // fill temporary pixel
        color_convert(rgb32f_pixel, gray_pixel);    // calculate luminance

        get_color(gray_pixel, gray_color_t()) =
                    std::pow(
                        get_color(gray_pixel, gray_color_t()),
                        gamma - 1.f
                        );

        get_color(rgb32f_pixel, red_t()) =
                channel_multiply(
                    get_color(rgb32f_pixel, red_t()),
                    get_color(gray_pixel, gray_color_t())
                    );
        get_color(rgb32f_pixel, green_t()) =
                channel_multiply(
                    get_color(rgb32f_pixel, green_t()),
                    get_color(gray_pixel, gray_color_t())
                    );
        get_color(rgb32f_pixel, blue_t()) =
                    get_color(rgb32f_pixel, blue_t()),
                    get_color(gray_pixel, gray_color_t())
                    );

        color_convert(rgb32f_pixel, dst);     // fill final pixel
    }
};

*/

template <typename C1, typename C2>
struct default_gamma_converter_impl
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst, float gamma) const
    {
        using namespace boost::gil;

        rgb32f_pixel_t rgb32f_pixel;                // create temporary pixel
        color_convert(src, rgb32f_pixel);           // fill temporary pixel

        get_color(rgb32f_pixel, red_t()) =
                std::pow(
                    get_color(rgb32f_pixel, red_t()),
                    gamma
                    );
        get_color(rgb32f_pixel, green_t()) =
                std::pow(
                    get_color(rgb32f_pixel, green_t()),
                    gamma
                    );
        get_color(rgb32f_pixel, blue_t()) =
                std::pow(
                    get_color(rgb32f_pixel, blue_t()),
                    gamma
                    );

        color_convert(rgb32f_pixel, dst);     // fill final pixel
    }
};


/*

template <>
struct default_gamma_converter_impl<
        boost::gil::rgb_t,
        boost::gil::rgb_t
        >
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst, float gamma) const
    {
        using namespace boost::gil;

        gray32f_pixel_t gray_pixel;
        color_convert(src, gray_pixel);         // calculate luminance

        const bits32f c_ =
                    std::pow(
                        get_color(gray_pixel, gray_color_t()),
                        gamma - 1.f
                        );            // use luminance to multiplication factor

        get_color(dst, red_t()) =
                channel_convert<typename color_element_type<DstP, red_t>::type>(
                    static_cast<bits32f>(
                        channel_multiply(
                            channel_convert<bits32f>(
                                get_color(src, red_t())
                                ),
                            c_)
                        )
                    );

        get_color(dst, green_t()) =
                channel_convert<typename color_element_type<DstP, green_t>::type>(
                    static_cast<bits32f>(
                        channel_multiply(
                            channel_convert<bits32f>(
                                get_color(src, green_t())
                                ),
                            c_)
                        )
                    );

        get_color(dst, blue_t()) =
                channel_convert<typename color_element_type<DstP, blue_t>::type>(
                    static_cast<bits32f>(
                        channel_multiply(
                            channel_convert<bits32f>(
                                get_color(src, blue_t())
                                ),
                            c_)
                        )
                    );
    }
};
*/

template <>
struct default_gamma_converter_impl<
        boost::gil::rgb_t,
        boost::gil::rgb_t
        >
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst, float gamma) const
    {
        using namespace boost::gil;

        get_color(dst, red_t()) =
                channel_convert<typename color_element_type<DstP, red_t>::type>(
                    static_cast<bits32f>(
                        std::pow(
                            channel_convert<bits32f>(
                                get_color(src, red_t())
                                ),
                            gamma)
                        )
                    );

        get_color(dst, green_t()) =
                channel_convert<typename color_element_type<DstP, green_t>::type>(
                    static_cast<bits32f>(
                        std::pow(
                            channel_convert<bits32f>(
                                get_color(src, green_t())
                                ),
                            gamma)
                        )
                    );

        get_color(dst, blue_t()) =
                channel_convert<typename color_element_type<DstP, blue_t>::type>(
                    static_cast<bits32f>(
                        std::pow(
                            channel_convert<bits32f>(
                                get_color(src, blue_t())
                                ),
                            gamma)
                        )
                    );
    }
};

struct default_gamma_converter
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst, float gamma) const
    {
        using namespace boost::gil;

        typedef typename color_space_type<SrcP>::type SrcColorSpace;
        typedef typename color_space_type<DstP>::type DstColorSpace;
        default_gamma_converter_impl<SrcColorSpace, DstColorSpace>()(src, dst, gamma);
    }
};

template <typename SrcP, typename DstP>
inline void gamma_convert(const SrcP& src, DstP& dst, float gamma)
{
    default_gamma_converter()(src, dst, gamma);
}

} // namespace libhdr

#endif // LIBHDR_GAMMA_HPP
