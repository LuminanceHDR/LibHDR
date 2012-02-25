#include <boost/lambda/lambda.hpp>
#include <boost/lambda/casts.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/cstdint.hpp>
#include <algorithm>
#include <iostream>
#include <xmmintrin.h>
#include <boost/date_time.hpp>
#include <set>

#include <libhdr/pixel.h>

#define PRINT_PIXEL_DIFF

const int SAMPLES = 4000000; //120;

uint8_t toUint8(float a)
{
    return static_cast<uint8_t>( (a*255.f) + 0.5f );
}

int main()
{
    using namespace boost::lambda;
    using namespace boost::posix_time;
    using namespace std;

    time_duration sse_execution_time;
    time_duration std_execution_time;

    srand( time(NULL) );

    // 10 mpixel = 40 milion floats
    float* buffer_f = static_cast<float*>(_mm_malloc(SAMPLES*sizeof(float), 16));
    uint8_t* buffer_u_std = static_cast<uint8_t*>(_mm_malloc(SAMPLES*sizeof(uint8_t), 16));
    uint8_t* buffer_u_sse = static_cast<uint8_t*>(_mm_malloc(SAMPLES*sizeof(uint8_t), 16));

    fill(buffer_f, buffer_f+4, 0.f);  // set first pixel to all zeros
    fill(buffer_f+4, buffer_f+8, 1.f);    // set second pixel to all ones
    generate(buffer_f+8, buffer_f+SAMPLES, ll_static_cast<float>( bind(rand))/RAND_MAX );

    // convert standard method!
    ptime start_t( microsec_clock::universal_time() );

    transform(buffer_f, buffer_f+SAMPLES, buffer_u_std, bind(&toUint8, _1));

    std_execution_time = microsec_clock::universal_time() - start_t;

    // fast SSE conversion
    uint32_t* buffer_i_sse = reinterpret_cast<uint32_t*>(buffer_u_sse);
    LibHDR::Pixel* pixels = reinterpret_cast<LibHDR::Pixel*>(buffer_f);

    start_t = microsec_clock::universal_time();

    transform(pixels, pixels+(SAMPLES>>2), buffer_i_sse, _1);   // automatic conversion from Pixel to uint32_t

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
    transform(buffer_u_std, buffer_u_std + SAMPLES, buffer_u_sse, inserter(check, check.begin()), _1 == _2 );
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
