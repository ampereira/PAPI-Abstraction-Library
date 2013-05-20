#include "../src/pal.hpp"
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

int main (int argc, char **argv) {
    vector< string > vst, vst2;

    if (argc > 1) {
        for (unsigned i = 1; i < (unsigned) argc; ++i) {
            string st = "PAPI_TOT_INS";
            vst.push_back(st);
        }
    } else {
        cerr << "The counters to measure must be passed as an argument!!" << endl;
        return -1;
    }


    string st1 = "PAPI_TOT_CYC";
    vst2.push_back(st1);
    string st2 = "PAPI_TOT_INS";
    vst2.push_back(st2);

	int m_id = PAL::Counters::new_measure (vst2);



	float a = 0;
	
	for (int i = 0; i < 5; ++i) {
		PAL::Counters::start_measure(m_id);
		a++;
		++a;
		++a;
		PAL::Counters::stop_measure(m_id);
	}

    PAL::Counters::print_results(m_id);

    return 0;
}
