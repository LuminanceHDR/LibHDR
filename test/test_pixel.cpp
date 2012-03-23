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

#define PRINT_PIXEL_DIFF

#ifndef PRINT_PIXEL_DIFF
#include <boost/lambda/lambda.hpp>
#endif
#include <boost/bind.hpp>
#include <boost/cstdint.hpp>
#include <boost/date_time.hpp>
#include <boost/random.hpp>
#include <algorithm>
#include <iostream>
#include <set>

#include <libhdr/pixel.h>

const int SAMPLES = 4000000; //120;

uint8_t toUint8(float a)
{
    return static_cast<uint8_t>( (a*255.f) + 0.5f );
}

int main()
{
    using namespace boost::posix_time;
    using namespace std;

    time_duration sse_execution_time;
    time_duration std_execution_time;

    boost::mt19937 rng;
    rng.seed(static_cast<unsigned int>(std::time(0)));
    boost::uniform_real<> unif_distrib(0.f, 1.f);

    boost::variate_generator<boost::mt19937&, boost::uniform_real<> > gen(rng, unif_distrib);

    float* buffer_f = static_cast<float*>(_mm_malloc(SAMPLES*sizeof(float), 16));
    uint8_t* buffer_u_std = static_cast<uint8_t*>(_mm_malloc(SAMPLES*sizeof(uint8_t), 16));
    uint8_t* buffer_u_sse = static_cast<uint8_t*>(_mm_malloc(SAMPLES*sizeof(uint8_t), 16));

    fill(buffer_f, buffer_f+4, 0.f);  // set first pixel to all zeros
    fill(buffer_f+4, buffer_f+8, 1.f);    // set second pixel to all ones
    generate(buffer_f+8, buffer_f+SAMPLES, gen);

    // convert standard method!
    ptime start_t( microsec_clock::universal_time() );

    transform(buffer_f, buffer_f+SAMPLES, buffer_u_std, boost::bind(&toUint8, _1));

    std_execution_time = microsec_clock::universal_time() - start_t;

    // fast SSE conversion
    uint32_t* buffer_i_sse = reinterpret_cast<uint32_t*>(buffer_u_sse);
    LibHDR::Pixel* pixels = reinterpret_cast<LibHDR::Pixel*>(buffer_f);

    start_t = microsec_clock::universal_time();

    copy(pixels, pixels+(SAMPLES>>2), buffer_i_sse);        // automatic conversion from Pixel to uint32_t

    sse_execution_time = microsec_clock::universal_time() - start_t;

#ifdef PRINT_PIXEL_DIFF
    int errors = 0;
    for (int idx = 0; idx < SAMPLES; ++idx)
    {
        if ( buffer_u_std[idx] != buffer_u_sse[idx] )
        {
            cerr << idx << " "
                 << (int)(buffer_u_std[idx])
                 << " != "
                 << (int)(buffer_u_sse[idx])
                 << " - "
                 << buffer_f[idx]
                 << " "
                 << (buffer_f[idx]*255.f)
                 << " "
                 << (int)((buffer_f[idx]*255.f) + 0.5 )
                 << "\n";
            errors++;
        }
    }

    cout << "Errors: " << errors << "/" << SAMPLES << "\n";
#else
    std::set<bool> check;
    transform(buffer_u_std, buffer_u_std + SAMPLES, buffer_u_sse,
              inserter(check, check.begin()), boost::lambda::_1 == boost::lambda::_2 );
#endif
    cout << "Standard method, execution time: " << std_execution_time << "\n";
    cout << "Vectorized method, execution time: " << sse_execution_time << endl;

    _mm_free(buffer_f);
    _mm_free(buffer_u_sse);
    _mm_free(buffer_u_std);

#ifdef PRINT_PIXEL_DIFF
    return (errors != 0);
#else
    return ( check.size() != 1 );
#endif
}
