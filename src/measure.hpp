#ifndef MEASURE
#define MEASURE

#include "eventset.hpp"

// GCC hacks for optimizing conditional blocks
#define likely(x)	__builtin_expect(!!(x), 1)	// likely for the condition to be true
#define unlikely(x)	__builtin_expect(!!(x), 0)	// unlikely for the condition to be true

class Measure {
	EventSet eventset;
	unsigned event_number;
	unsigned event_rep;
	unsigned repetitions;
	bool predefined_reps;

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
