#include "../src/pal.hpp"
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
        cerr << "The counters to measure must be passed as an argument!!" << endl;
        return -1;
    }

	int m_id = PAL::Counters::new_measure (vst.size());

    for (unsigned i = 0; i < 1; ++i) {
        float a = 0;
        PAL::Counters::start_measure(m_id);
        a++;
        ++a;
        ++a;
        PAL::Counters::stop_measure(m_id);
    }

    PAL::Counters::print_results(m_id);

    return 0;
}
