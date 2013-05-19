#ifndef PAL
#define PAL

#include "measure.hpp"
#include <cstdlib>
#include <string>


namespace pal {
	std::vector<EventSet> event_sets;
	std::vector<Measure> measurements;

	Measure new_measure (std::vector<std::string>);
}

#endif
