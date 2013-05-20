#ifndef PAL_LIB
#define PAL_LIB

#include "measure.hpp"
#include <cstdlib>
#include <string>
#include <papi.h>


namespace PAL {
	namespace Counters {

		int new_measure (std::vector<std::string>);
		bool start_measure (unsigned);
		bool stop_measure (unsigned);
		void print_results (unsigned);
	}
}

#endif
