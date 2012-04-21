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
