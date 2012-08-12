#include "papi_lib.h"

using namespace std;

bool PAL::create_events (std::vector< string > evts) {
	int size = evts.size(), retval, index = 0;
	vector< int > event_codes (size);
	char error[PAPI_MAX_STR_LEN], *ev_name;
	bool conflict = false;

	// Creates the counters from their names
	for (vector< string >::iterator it = evts.begin(); it < evts.end(); ++it) {
		int ev;
		ev_name = (char *) it->c_str();
		retval = PAPI_event_name_to_code (ev_name, &ev);

		if (retval != PAPI_OK) {
			PAPI_perror(retval, error, PAPI_MAX_STR_LEN);

			cerr << "PAL | error on counter " << *it << " - " << error << endl;
			cerr << "PAL | counter will not be added to the measurements." << endl;
		} else {
			event_codes.push_back(ev);
		}
	}

	// Creates the eventsets from the counters - tries to group compatible counters
	for (vector< int >::iterator it = event_codes.begin(); it < event_codes.end(); ++it) {
		if (eventset.size() == 0 || conflict){
			eventset.push_back(-1);
			retval = PAPI_create_eventset(&eventset.back());

			if (conflict)
				conflict = false;
		}
		if (retval != PAPI_OK) {
			PAPI_perror(retval, error, PAPI_MAX_STR_LEN);

			cerr << "PAL | could not create eventset - " << error << endl;
			cerr << "PAL | library will exit." << endl;

			return false;
		}

		retval = PAPI_add_event(eventset.back(), *it);

		switch (retval) {
			case PAPI_OK 	  : break;
			case PAPI_ECNFLCT : conflict = true; break;
			default : cerr << "PAL | error adding counter to eventset - " << error << endl;
					  cerr << "PAL | library will exit." << endl;
					  return false;
		}
	}
}
