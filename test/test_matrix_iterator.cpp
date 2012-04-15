#include <libhdr/matrix.h>
#include <libhdr/details/misc.h>
#include <cassert>

using namespace LibHDR;

int main(int argc, char** argv)
{
    LIBHDR_POSSIBLY_UNUSED(argc);
    LIBHDR_POSSIBLY_UNUSED(argv);

    typedef Matrix<float> MatrixF;

    MatrixF m(10, 10);

    MatrixF::ConstIterator it = m.begin();
    MatrixF::ConstColIterator itEnd = m.end();

    // MatrixF::iterator it2 = it;  // invalid!

    const float* v = m.constData();

    if (v != &(*it)) return 1;
    if ((v + m.getCols()*m.getRows()) != &(*itEnd)) return 1;




    return 0;
}
