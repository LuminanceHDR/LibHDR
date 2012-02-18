#include "libhdr/io/framewriter.h"
#include "libhdr/frame.h"
#include "mockcallback.h"

#include <boost/shared_ptr.hpp>
#include <cstdlib>

using namespace LibHDR;

const int WIDTH = 4000;
const int HEIGTH = 3000;

int main(int /*argc*/, char */*argv*/[])
{
    // create TIFF Writer
    boost::shared_ptr< IO::FrameWriter > writer( IO::FrameWriterFactory::instance().create("tif") );

    // create empty frame, with red Pixel(s)
    Frame frame(WIDTH, HEIGTH);
    Pixel* fdata = reinterpret_cast<Pixel*>(frame.data());
    for (int idx = 0; idx < WIDTH*HEIGTH; ++idx)
    {
        fdata[idx] = Pixel(1.f, 0.f, 0.f);  // R G B
    }

    // Callback!
    LibHDRTest::MockCallback cb;
    writer->subscribe(&cb);

    try
    {
        writer->open("test.tif");
        writer->writeFrame( frame );
        writer->close();
    }
    catch (...)
    {
        std::cerr << "Could not write the file to test.tif" << std::endl;
    }

    return 0;
}
