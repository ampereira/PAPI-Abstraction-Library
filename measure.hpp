#ifndef MEASURE
#define MEASURE

#include "eventset.hpp"

class Measure {
	EventSet eventset;
	unsigned event_number;
	unsigned event_rep;
	unsigned repetitions;

public:
	Measure (EventSet&, unsigned);
	bool start (void);
	bool stop (void);
	void print (void);
	unsigned iterations (void);
	void add_result(unsigned, long long unsigned);
	EventSet get_eventset(void) const;
};

#endif
