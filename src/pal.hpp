#ifndef PAL_LIB
#define PAL_LIB

#include "measure.hpp"
#include <cstdlib>
#include <string>
#include <papi.h>

#ifndef MAIN
	#define SCOPE extern
#else
	#define SCOPE
#endif

namespace PAL {
	namespace Counters {
		SCOPE bool lib_initialized = false;
		SCOPE std::vector<EventSet> event_sets;
		SCOPE std::vector<Measure> measurements;

		int new_measure (std::vector<std::string>);
		bool start_measure (unsigned);
		bool stop_measure (unsigned);
		void print_results (unsigned);
	}
}

#endif
