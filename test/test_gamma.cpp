#include <boost/gil/image.hpp>
#include <boost/gil/extension/io_new/jpeg_all.hpp>
#include <libhdr/gamma.hpp>
#include <string>

using namespace boost::gil;
using namespace std;

int main(int argc, char** argv)
{
    string in_filename = argv[1];
    string out_filename = argv[2];

    // rgb32f_image_t img;
    rgb8_image_t img;
    // read_image( in_filename, img, tiff_tag() );
    read_image( in_filename, img, jpeg_tag() );

    libhdr::gamma_correction( const_view(img), view(img) );

    write_view( out_filename
              , const_view( img )
              , image_write_info< jpeg_tag >( 95 )
              );

    return 0;
}
