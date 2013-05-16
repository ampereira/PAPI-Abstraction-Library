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
	unsigned eventset_size;	// amount of eventsets
	unsigned total_events;  // amount of events
	std::vector<Event> event_list;

public:
	EventSet ();
	EventSet (int);
	EventSet (std::vector<std::string>);
	bool create (std::vector<std::string>);
	/*inline*/ int operator[] (unsigned);
	inline unsigned size (void) {return event_list.size(); }
	Event get_event (unsigned);
	unsigned number_of_events (void);
};

#endif
