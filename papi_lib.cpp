#include "papi_lib.h"

using namespace std;

// TODO: Contadores repetidos? e se todos errados?
bool PAL::create_events (vector< string > evts) {
	int size = evts.size(), retval;
	vector< int > event_codes (size);
	char error[PAPI_MAX_STR_LEN];
	bool conflict = false;

	// Creates the counters from their names
	for (vector< string >::iterator it = evts.begin(); it < evts.end(); ++it) {
		int ev;
		retval = PAPI_event_name_to_code ((char *) it->c_str(), &ev);

		if (retval != PAPI_OK) {
			PAPI_perror(retval, error, PAPI_MAX_STR_LEN);

			cerr << "PAL | error on counter " << *it << " - " << error << endl;
			cerr << "PAL | counter will not be added to the measurements." << endl;
		} else {
			event_codes.push_back(ev);
		}
	}
int coisas;
	// Creates the eventsets from the counters - tries to group compatible counters
	for (vector< int >::iterator it = event_codes.begin(); it < event_codes.end(); ++it) {
		if (eventset.size() == 0 || conflict){
			eventset.push_back(-1);
			//retval = PAPI_create_eventset(&eventset.back());
			retval = PAPI_create_eventset(&coisas);

			if (conflict)
				conflict = false;

			if (retval != PAPI_OK) {
				PAPI_perror(retval, error, PAPI_MAX_STR_LEN);

				cerr << "PAL | could not create eventset - " << error << endl;
				cerr << "PAL | library will exit." << endl;

				return false;
			}
		}

		retval = PAPI_add_event(coisas, *it);

		cout << "coisas " << coisas << " " << *it << endl;

		switch (retval) {
			case PAPI_OK 	  : break;
			case PAPI_ECNFLCT : conflict = true; break; // se isto acontece o iterator nao pode ser incrementado...
			default : PAPI_perror(retval, error, PAPI_MAX_STR_LEN);
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
