#include "measure.hpp"
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

int main (void) {
    EventSet pal (3);

    vector< string > st;
    string st1 = "PAPI_FP_OPS";
    string st2 = "PAPI_L2_TCM";
    string st3 = "PAPI_L2_DCM";

    st.push_back(st1);
    st.push_back(st2);
    st.push_back(st3);

    PAPI_library_init(PAPI_VER_CURRENT);

    pal.create(st);

    Measure mm (&pal, 3);

    for (unsigned i = 0; i < mm.iterations(); ++i) {
        float a = 0;
        mm.start();
        a++;
        ++a;
        ++a;
        mm.stop();
    }

    mm.print();

    return 0;
}