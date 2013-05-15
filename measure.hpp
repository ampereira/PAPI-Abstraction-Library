#ifndef MEASURE
#define MEASURE

#include "eventset.hpp"

class Measure {
	EventSet eventset;
	unsigned event_number;
	unsigned event_rep;
	unsigned repetitions;

public:
	Measure (EventSet, unsigned);
	bool start (void);
	bool stop (void);
	void print (void);
	unsigned iterations (void);
};

#endif
