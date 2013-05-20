#include "pal.hpp"

using namespace std;

namespace PAL {
	namespace Counters {
		bool lib_initialized = false;
		std::vector<EventSet> event_sets;
		std::vector<Measure> measurements;

		int new_measure (vector<string> counters) {

			if (!lib_initialized) {
				int retval = PAPI_library_init(PAPI_VER_CURRENT);
				
				if (retval != PAPI_OK) {
					char *error;
					error = PAPI_strerror(retval);

					cerr << "PAL | Error initializing PAPI - " << error << " - " << retval << endl;

					return -1;
				} else
					lib_initialized = true;
			}
			
			EventSet ev (counters);
			Measure mm (ev);

			//event_sets.push_back(ev);
			measurements.push_back(mm);

			return measurements.size() - 1;
		}

		bool start_measure (unsigned m_id) {
			return measurements[m_id].start();
		}

		bool stop_measure (unsigned m_id) {
			return measurements[m_id].stop();
		}

		void print_results (unsigned m_id) {
			measurements[m_id].print();
		}
	}
}