#include "libhdr/io/framewriter.h"
#include "libhdr/frame.h"

#include <boost/shared_ptr.hpp>
#include <cstdlib>

using namespace LibHDR;

float getRandZeroToOne()
{
    return static_cast<float>(rand())/RAND_MAX;
}

const int WIDTH = 100;
const int HEIGTH = 80;

int main(int argc, char *argv[])
{
    srand( time(NULL) );

    // create TIFF Writer
    boost::shared_ptr< IO::FrameWriter > writer( IO::FrameWriterFactory::instance().create("tif") );

    // create empty frame, with random data
    Frame frame(WIDTH, HEIGTH);
    float* fdata = frame.data();
    for (int idx = 0; idx < WIDTH*HEIGTH*4; ++idx)
    {
        fdata[idx] = getRandZeroToOne();
    }

    try
    {
        writer->open("test.tif");
        writer->writeFrame( frame );
        //writer->close();
    }
    catch (...)
    {
        std::cerr << "Che cazzo e' successo?" << std::endl;
    }

    return 0;
}
