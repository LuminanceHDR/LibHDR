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

namespace detail
{

template <typename Out>
struct pixel_compressor
{
    pixel_compressor(const compressor_params& params)
        : params_(params),
          compressor_factor_(params.white_point() -
                             params.black_point())
    {}

    template <typename In>
    Out operator()(const In& in)
    {
        using namespace boost::gil;

        return Out( rgb32f_pixel_t(
                        (( channel_convert<bits32f>(
                               get_color(in, red_t()))
                           * compressor_factor_ )
                         + params_.black_point()) * 255.f,
                        (( channel_convert<bits32f>(
                               get_color(in, green_t()))
                           * compressor_factor_ )
                         + params_.black_point()) * 255.f,
                        (( channel_convert<bits32f>(
                               get_color(in, blue_t()))
                           * compressor_factor_ )
                         + params_.black_point()) * 255.f
                        ) );
    }
private:
    const compressor_params& params_;
    float compressor_factor_;
};

}

template <typename SrcView, typename DstView>
void compressor(const SrcView& src,
                const DstView& dst,
                const compressor_params& params)
{
    using namespace boost::gil;
    using namespace std;

    gil_function_requires<ImageViewConcept<SrcView> >();
    gil_function_requires<MutableImageViewConcept<DstView> >();
    gil_function_requires<ColorSpacesCompatibleConcept<
            typename color_space_type<SrcView>::type,
            typename color_space_type<DstView>::type> >();

    ::std::transform(src.begin(), src.end(),
                     dst.begin(),
                     detail::pixel_compressor<
                     typename DstView::value_type>(params));
}

}

#endif // LIBHDR_COMPRESSOR_HPP
