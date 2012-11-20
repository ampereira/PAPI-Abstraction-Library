#include "eventset.hpp"

using namespace std;

EventSet::EventSet (int num_events) {
	events = new int [num_events];
	events_size = 0;
}

//inline 
int EventSet::operator[] (unsigned index) {
	if (index >= events_size) {
		try {
			throw OUT_OF_BOUNDS;
		} catch (Error e) {
			cerr << "PAL | EventSet: index out of bounds: " << index << endl;
			cerr << "PAL | EventSet: at file " << __FILE__ << ", line " << __LINE__ - 5 << endl;
		}
		return -1;
	} else
		return events[index];
}

bool EventSet::create (vector<string> evts) {
	unsigned size = evts.size(), event_codes_index = 0;
	int event_codes [size], retval;
	char *error;
	bool conflict = false;

	// Creates the counters from their names
	for (vector< string >::iterator it = evts.begin(); it < evts.end(); ++it) {
		int ev;
		retval = PAPI_event_name_to_code ((char *) it->c_str(), &ev);

		if (retval != PAPI_OK) {
			error = PAPI_strerror(retval);

			cerr << "PAL | EventSet: error on counter " << *it << " - " << error << endl;
			cerr << "PAL | EventSet: counter will not be added to the measurements." << endl;
		} else {
			Event evn ((char*) it->c_str(), ev);
			event_list.push_back(evn);
			event_codes[event_codes_index] = ev;
			++event_codes_index;
		}
	}

	// Creates the eventsets from the counters - tries to group compatible counters
	// problema: if conflict cria eventset novo antes de ver se da nos restantes
	unsigned it = 0;
	while (it < size) {
		if (events_size == 0 || conflict){
			events[events_size] = PAPI_NULL;
			++events_size;

			retval = PAPI_create_eventset(&events[events_size - 1]);

			if (conflict)
				conflict = false;

			if (retval != PAPI_OK) {
				error = PAPI_strerror(retval);

				cerr << "PAL | EventSet: could not create eventset - " << error << endl;
				cerr << "PAL | EventSet: library will exit." << endl;

				return false;
			}
		}

		retval = PAPI_add_event(events[events_size - 1], event_codes[it]);

		switch (retval) {
			case PAPI_OK 	  : ++it; break;
			case PAPI_ECNFLCT : conflict = true; break;
			default : error = PAPI_strerror(retval);
					  cerr << "PAL | EventSet: error adding counter to eventset - " << error << endl;
					  cerr << "PAL | EventSet: library will exit." << endl;
					  return false;
		}
	}
	return true;
}
