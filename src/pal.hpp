#ifndef PAL
#define PAL

#include "measure.hpp"
#include <cstdlib>
#include <string>


namespace PAL {
	namespace Counters {
		std::vector<EventSet> event_sets;
		std::vector<Measure> measurements;

		int new_measure (std::vector<std::string>);
		bool start_measure (unsigned);
		bool stop_measure (unsigned);
		void print_results (unsigned);
	}
}

#endif
