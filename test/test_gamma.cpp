#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE gamma_convert

#include <boost/test/unit_test.hpp>

#define TEST_CHECK_CLOSE(a, b) \
    BOOST_CHECK_CLOSE(a, b, 0.0005f)

#include <iostream>
#include <cmath>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/toolbox/xyz.hpp>
#include <libhdr/gamma.hpp>

using namespace boost;
using namespace std;

BOOST_AUTO_TEST_SUITE(gamma_convert_test_gamma_1)

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_gray)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.5, 0.5, 0.5);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 1.0f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 0.5f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 0.5f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 0.5f);
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_white)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(1.f, 1.f, 1.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 1.f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 1.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 1.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 1.f);
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_red)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(1.f, 0.f, 0.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 1.f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 1.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 0.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 0.f);
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_green)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.f, 1.f, 0.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 1.f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 0.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 1.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 0.f);
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_blue)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.f, 0.f, 1.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 1.f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 0.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 0.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 1.f);
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_black)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.f, 0.f, 0.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 1.f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]), 0.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]), 0.f);
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]), 0.f);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(gamma_convert_test_gamma_22)

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_gray)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.5, 0.5, 0.5);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 2.2f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     pow(0.5f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     pow(0.5f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     pow(0.5f, 2.2f));
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_white)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(1.f, 1.f, 1.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 2.2f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     pow(1.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     pow(1.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     pow(1.f, 2.2f));
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_red)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(1.f, 0.f, 0.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 2.2f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     pow(1.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     pow(0.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     pow(0.f, 2.2f));
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_green)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.f, 1.f, 0.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 2.2f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     pow(0.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     pow(1.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     pow(0.f, 2.2f));
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_blue)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.f, 0.f, 1.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 2.2f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     pow(0.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     pow(0.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     pow(1.f, 2.2f));
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_black)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.f, 0.f, 0.f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 2.2f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     pow(0.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     pow(0.f, 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     pow(0.f, 2.2f));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(gamma_convert_test_gamma_mixed)

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb8u_rgb8u_1)
{
    const float GaMmA = 1.8f;

    gil::rgb8_pixel_t rgb8_pixel_src(128, 127, 126);
    gil::rgb8_pixel_t rgb8_pixel_dst;

    libhdr::gamma_convert(rgb8_pixel_src, rgb8_pixel_dst, GaMmA);

    BOOST_CHECK_EQUAL(rgb8_pixel_dst[0],
                      static_cast<boost::gil::bits8>(
                          255.f*std::pow(
                              static_cast<float>(rgb8_pixel_src[0])/255.f, GaMmA) + 0.5f)
                      );
    BOOST_CHECK_EQUAL(rgb8_pixel_dst[1],
                      static_cast<boost::gil::bits8>(
                          255.f*std::pow(
                              static_cast<float>(rgb8_pixel_src[1])/255.f, GaMmA) + 0.5f)
                      );
    BOOST_CHECK_EQUAL(rgb8_pixel_dst[2],
                      static_cast<boost::gil::bits8>(
                          255.f*std::pow(
                              static_cast<float>(rgb8_pixel_src[2])/255.f, GaMmA) + 0.5f)
                      );
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb8u_rgb8u_2)
{
    const float GaMmA = 1.4f;

    gil::rgb8_pixel_t rgb8_pixel_src(43, 21, 210);
    gil::rgb8_pixel_t rgb8_pixel_dst;

    libhdr::gamma_convert(rgb8_pixel_src, rgb8_pixel_dst, GaMmA);

    BOOST_CHECK_EQUAL(rgb8_pixel_dst[0],
                      static_cast<boost::gil::bits8>(
                          255.f*std::pow(
                              static_cast<float>(rgb8_pixel_src[0])/255.f, GaMmA) + 0.5f)
                      );
    BOOST_CHECK_EQUAL(rgb8_pixel_dst[1],
                      static_cast<boost::gil::bits8>(
                          255.f*std::pow(
                              static_cast<float>(rgb8_pixel_src[1])/255.f, GaMmA) + 0.5f)
                      );
    BOOST_CHECK_EQUAL(rgb8_pixel_dst[2],
                      static_cast<boost::gil::bits8>(
                          255.f*std::pow(
                              static_cast<float>(rgb8_pixel_src[2])/255.f, GaMmA) + 0.5f)
                      );
}



BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_random_1)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.23f, 0.76f, 0.45f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 2.2f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     pow(rgb32f_pixel_src[0], 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     pow(rgb32f_pixel_src[1], 2.2f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     pow(rgb32f_pixel_src[2], 2.2f));
}


BOOST_AUTO_TEST_CASE(gamma_convert_test_rgb32f_rgb32f_random_2)
{
    gil::rgb32f_pixel_t rgb32f_pixel_src(0.23f, 0.76f, 0.45f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;

    libhdr::gamma_convert(rgb32f_pixel_src, rgb32f_pixel_dst, 2.6f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     pow(rgb32f_pixel_src[0], 2.6f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     pow(rgb32f_pixel_src[1], 2.6f));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     pow(rgb32f_pixel_src[2], 2.6f));
}

BOOST_AUTO_TEST_CASE(gamma_convert_test_xyz32f_rgb32f)
{
    gil::xyz32f_pixel_t xyz32f_pixel_src(.2f, .1f, 0.7f);
    gil::rgb32f_pixel_t rgb32f_pixel_dst;
    gil::xyz32f_pixel_t xyz32f_pixel_dst;

    libhdr::gamma_convert(xyz32f_pixel_src, rgb32f_pixel_dst, 1.f);

    gil::color_convert(rgb32f_pixel_dst, xyz32f_pixel_dst);

    TEST_CHECK_CLOSE(static_cast<float>(xyz32f_pixel_dst[0]),
                     static_cast<float>(xyz32f_pixel_src[0]));
    TEST_CHECK_CLOSE(static_cast<float>(xyz32f_pixel_dst[1]),
                     static_cast<float>(xyz32f_pixel_src[1]));
    TEST_CHECK_CLOSE(static_cast<float>(xyz32f_pixel_dst[2]),
                     static_cast<float>(xyz32f_pixel_src[2]));

    gil::rgb32f_pixel_t rgb32f_pixel_dst2;
    gil::rgb32f_pixel_t rgb32f_pixel_dst3;

    gil::color_convert(xyz32f_pixel_src, rgb32f_pixel_dst2);
    libhdr::gamma_convert(rgb32f_pixel_dst2, rgb32f_pixel_dst3, 1.f);

    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[0]),
                     static_cast<float>(rgb32f_pixel_dst3[0]));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[1]),
                     static_cast<float>(rgb32f_pixel_dst3[1]));
    TEST_CHECK_CLOSE(static_cast<float>(rgb32f_pixel_dst[2]),
                     static_cast<float>(rgb32f_pixel_dst3[2]));
}

BOOST_AUTO_TEST_SUITE_END()
