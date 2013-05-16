#include "measure.hpp"
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

int main (int argc, char **argv) {
    vector< string > vst;

    if (argc > 1) {
        for (unsigned i = 1; i < argc; ++i) {
            string st = argv[i];
            vst.push_back(st);
        }
    } else {
        cout << "The counters to measure must be passed as an argument!!" << endl;
        return -1;
    }


    PAPI_library_init(PAPI_VER_CURRENT);

	EventSet pal (vst.size());
    pal.create(vst);

    cout << pal[0] << endl;

    Measure mm (pal, 1);


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
