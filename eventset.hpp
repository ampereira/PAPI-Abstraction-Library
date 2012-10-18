#ifndef EVENTSET 
#define EVENTSET 

#include <papi.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "errors.hpp"
#include "event.hpp"

class EventSet {
	int *events;
	unsigned events_size;
	std::vector<Event> event_list;

public:
	EventSet (int);
	bool create (std::vector<std::string>);
	inline int operator[] (unsigned);
};

#endif
