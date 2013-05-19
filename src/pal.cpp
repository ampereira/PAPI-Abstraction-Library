#include "pal.hpp"

using namespace std;

namespace pal {
	Measure new_measure (vector<string> counters) {
    	PAPI_library_init(PAPI_VER_CURRENT);
		
		EventSet ev (counters);
		Measure mm (ev);

		event_sets.push_back(ev);
		measurements.push_back(mm);
	}
}