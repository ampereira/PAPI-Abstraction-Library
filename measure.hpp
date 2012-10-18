#ifndef MEASURE
#define MEASURE

#include "eventset.hpp"

class Measure {

public:
	Measure (EventSet);
	bool start ();
	bool stop ();
};

#endif
