#ifndef PAL_LIB
#define PAL_LIB

#include "measure.hpp"
#include <cstdlib>
#include <string>
#include <papi.h>


namespace PAL {
	namespace Counters {
		bool lib_initialized = false;
		std::vector<EventSet> event_sets;
		std::vector<Measure> measurements;

		int new_measure (std::vector<std::string>);
		bool start_measure (unsigned);
		bool stop_measure (unsigned);
		void print_results (unsigned);
	}
}

#endif
