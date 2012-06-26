#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE range_compressor

#include <boost/test/unit_test.hpp>

#define TEST_CHECK_CLOSE(a, b) \
    BOOST_CHECK_CLOSE(a, b, 0.0005f)

#include <iostream>
#include <cmath>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/toolbox/xyz.hpp>
#include <libhdr/compressor.hpp>

using namespace boost;
using namespace std;

BOOST_AUTO_TEST_SUITE(range_compressor_test_gamma_1)

BOOST_AUTO_TEST_CASE(range_compressor_test_rgb32f_rgb32f_1)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.f, 0.5f, 1.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::range_compressor(rgb32f_pixel_src, rgb32f_pixel_dst,
                          libhdr::compressor_params(0.2f, 0.8f));

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 0.2f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 0.5f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 0.8f);
}

BOOST_AUTO_TEST_CASE(range_compressor_test_rgb32f_rgb32f_2)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.f, 0.5f, 1.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::range_compressor(rgb32f_pixel_src, rgb32f_pixel_dst,
                          libhdr::compressor_params(0.f, 0.8f));

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 0.0f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 0.4f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 0.8f);
}

BOOST_AUTO_TEST_CASE(range_compressor_test_rgb8_rgb32f_1)
{
    gil::rgb8_pixel_t rgb8_pixel_src(0, 126, 255);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::range_compressor(rgb8_pixel_src, rgb32f_pixel_dst,
                          libhdr::compressor_params(0.f, 0.85f));

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 0.0f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 0.42f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 0.85f);
}

BOOST_AUTO_TEST_SUITE_END()
