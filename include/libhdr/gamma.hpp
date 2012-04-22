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

//! \file gamma.h
//!
//! \brief Gamma adjustment algorithm
//! \author Davide Anastasia <davideanastasia@users.sourceforge.net>
//! \date 2012-04-21
//! \since 0.0.1

#ifndef LIBHDR_GAMMA_HPP
#define LIBHDR_GAMMA_HPP

#include <boost/gil/gil_all.hpp>
#include <cmath>

namespace libhdr
{
const float DEFAULT_GAMMA = 1.8f;

template <typename Out>
struct gamma_correction_channels
{
    gamma_correction_channels(float gamma = DEFAULT_GAMMA):
        gamma_(1.f/gamma)
    {}

    template <typename T>
    Out operator()(const T& in1)
    {
        return Out(255.f*powf(static_cast<float>(in1)/255.f, gamma_));
    }

private:
    float gamma_;
};

template <typename SrcView, typename DstView>
void gamma_correction(const SrcView& src, const DstView& dst,
                      float gamma = DEFAULT_GAMMA)
{
    using namespace boost::gil;
/*
    gil_function_requires<ImageViewConcept<SrcView> >();
    gil_function_requires<MutableImageViewConcept<DstView> >();
    gil_function_requires<ColorSpacesCompatibleConcept<
            typename color_space_type<SrcView>::type,
            typename color_space_type<DstView>::type> >();
*/
    typedef typename channel_type<DstView>::type dst_channel_t;

    typename SrcView::iterator src_it = src.begin();
    for (typename DstView::iterator dst_it = dst.begin();
         dst_it != dst.end();
         ++dst_it, ++src_it)
    {
        static_transform(*src_it, *dst_it,
                         gamma_correction_channels<dst_channel_t>(gamma));
    }
}




}

#endif // LIBHDR_GAMMA_HPP
