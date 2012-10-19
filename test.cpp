#include "measure.hpp"
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

int main (void) {
    EventSet pal (10);

    vector< string > st;
    string st1 = "PAPI_TOT_CYC";
    string st2 = "PAPI_L2_TCM";
    string st3 = "PAPI_L2_DCM";

    st.push_back(st1);
    st.push_back(st2);
    st.push_back(st3);

    PAPI_library_init(PAPI_VER_CURRENT);

    pal.create(st);

    return 0;
}
