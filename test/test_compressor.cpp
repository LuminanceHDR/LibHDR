#include <boost/gil/image.hpp>
#include <boost/gil/extension/io_new/jpeg_all.hpp>
#include <libhdr/compressor.hpp>
#include <string>

using namespace boost::gil;
using namespace std;

int main(int argc, char** argv)
{
    string in_filename = argv[1];
    string out_filename = argv[2];

    rgb8_image_t img;
    read_image( in_filename, img, jpeg_tag() );

    libhdr::compressor( const_view(img), view(img),
                        libhdr::compressor_params(0.2, 0.8) );

    write_view( out_filename
              , const_view( img )
              , image_write_info< jpeg_tag >( 95 )
              );

    return 0;
}
