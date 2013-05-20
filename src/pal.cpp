#include "pal.hpp"

using namespace std;

namespace PAL {
	namespace Counters {
		std::vector<Measure> measurements;

		int new_measure (vector<string> counters) {

			PAPI_library_init(PAPI_VER_CURRENT);
			
			EventSet ev (counters);
			Measure mm (ev);
			cout << ev.size() << endl;

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