#include "libhdr/io/framewriter.h"
#include "libhdr/io/framereader.h"
#include "libhdr/image.h"
#include "mockcallback.h"

#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <iostream>

using namespace LibHDR;
using namespace std;
using namespace boost;

int main(int argc, char** argv)
{
    std::string in_file;
    std::string out_file;
    if (argc >= 3)
    {
        in_file = argv[1];
        out_file = argv[2];
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return -1;
    }

    LibHDRTest::MockCallback cb;
    try
    {
        // create TIFF Writer
        shared_ptr< IO::FrameWriter > writer( IO::FrameWriterFactory::instance().create("tif") );
        // create JPG Reader
        shared_ptr< IO::FrameReader > reader( IO::FrameReaderFactory::instance().create("jpg") );

        // Subscribe
        writer->subscribe(&cb);
        reader->subscribe(&cb);

        reader->open(in_file);
        ImagePtr read_frame( reader->readFrame(Settings()) );
        reader->close();

        cout << read_frame->exifData() << endl;

        writer->open(out_file);
        writer->writeFrame( read_frame );
        writer->close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

}
