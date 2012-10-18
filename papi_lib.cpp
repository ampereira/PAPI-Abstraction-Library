#include "papi_lib.h"

using namespace std;

// TODO: Contadores repetidos? e se todos errados?
bool PAL::create_events (vector< string > evts) {
	int size = evts.size(), retval;
	vector< int > event_codes (size);
	char *error;
	bool conflict = false;

	// Creates the counters from their names
	for (vector< string >::iterator it = evts.begin(); it < evts.end(); ++it) {
		int ev;
		retval = PAPI_event_name_to_code ((char *) it->c_str(), &ev);

		if (retval != PAPI_OK) {
			error = PAPI_strerror(retval);

			cerr << "PAL | error on counter " << *it << " - " << error << endl;
			cerr << "PAL | counter will not be added to the measurements." << endl;
		} else {
			event_codes.push_back(ev);
		}
	}

	// Creates the eventsets from the counters - tries to group compatible counters
	for (unsigned it = 0; it < event_codes.size(); ++it) {
		if (eventset_size == 0 || conflict){
			eventset(PAPI_NULL);
			++eventset_size;

			cout << "evset " << PAPI_NULL << " " << eventset.back() << endl;
			retval = PAPI_create_eventset(&eventset.back());

			if (conflict)
				conflict = false;

			if (retval != PAPI_OK) {
				error = PAPI_strerror(retval);

				cerr << "PAL | could not create eventset - " << error << endl;
				cerr << "PAL | library will exit." << endl;

				return false;
			}
		}
		cout << "coisas " << eventset.back() << " " << event_codes[it] << " " << PAPI_TOT_INS << endl;

		retval = PAPI_add_event(eventset.back(), event_codes[it]);

		switch (retval) {
			case PAPI_OK 	  : break;
			case PAPI_ECNFLCT : conflict = true; break; // se isto acontece o iterator nao pode ser incrementado...
			default : error = PAPI_strerror(retval);
					  cerr << "PAL | error adding counter to eventset - " << error << endl;
					  cerr << "PAL | library will exit." << endl;
					  return false;
		}
	}

	return true;
}

int main(void){
        PAL *pal = new PAL();

        vector< string > st;
        string st1 = "PAPI_TOT_CYC";
        string st2 = "PAPI_TOT_INS";
        string st3 = "PAPI_L2_DCM";

        st.push_back(st1);
        st.push_back(st2);
        st.push_back(st3);

        PAPI_library_init(PAPI_VER_CURRENT);

        pal->create_events(st);

        return 0;
}
