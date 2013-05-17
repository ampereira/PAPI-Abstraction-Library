#include "measure.hpp"
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

int main (int argc, char **argv) {
    vector< string > vst;

    if (argc > 1) {
        for (unsigned i = 1; i < (unsigned) argc; ++i) {
            string st = argv[i];
            vst.push_back(st);
        }
    } else {
        cout << "The counters to measure must be passed as an argument!!" << endl;
        return -1;
    }



	EventSet pal (vst.size());
    pal.create(vst);
    int a;
    PAPI_event_name_to_code ((char *) vst[0].c_str(), &a);

    cout << pal.get_event(0).get_code() << " - " << PAPI_TOT_CYC << " - " << PAPI_TOT_INS << endl;

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
