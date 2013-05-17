#include "measure.hpp"

using namespace std;

Measure::Measure (EventSet &es, unsigned rp) {
	eventset = es;
	event_number = 0;
	event_rep = 0;
	repetitions = rp;
}

// cada vez que se executa o par start stop mede um evento
// para ja so mede uma vez cada evento
bool Measure::start (void) {
	int retval;
	char *error;

	if (event_number <= eventset.size()) {
		retval = PAPI_start(eventset[event_number]);

		if (retval != PAPI_OK) {
			error = PAPI_strerror(retval);

			cerr << "PAL | Measure: error measuring event - " << error << endl;
			cerr << "PAL | Measure: skipping event." << endl;

			return false;
		} else {
			return true;
		}
	} else {
		cerr << "PAL | Measure: all events were already measured." << endl;
		return false;
	}
}

bool Measure::stop (void) {
	int retval;
	char *error;
	long long int *counter_value;
	
	if (event_number <= eventset.size()) {
		retval = PAPI_stop(eventset[event_number], counter_value);

		if (retval != PAPI_OK) {
			error = PAPI_strerror(retval);

			cerr << "PAL | Measure: error measuring event - " << error << endl;
			cerr << "PAL | Measure: skipping event." << endl;

			++event_number;
			return false;
		} else {
	cout << "CHEGOU " << event_number << endl;

			eventset.add_result(event_number, (long long unsigned) counter_value[event_number]);

			if (event_rep < repetitions)
				++event_rep;
			else {
				event_rep = 0;
				++event_number;
			}

			return true;
		}

	} else {
		cerr << "PAL | Measure: all events were already measured." << endl;
		return false;
	}
}

void Measure::print (void) {
	cout << endl << endl << endl;
	cout << "\tPAPI Abstraction Library" << endl << endl;
	cout << "Presenting measurements results" << endl << endl;
	cout << "Counter\t\tMin\tMean\tMedian" << endl;

	for (unsigned i = 0; i < (unsigned) eventset.size(); ++i) {
		Event evt = eventset.get_event(i);
		cout << evt.get_name() << "\t" << evt.min() << "\t";
		cout << evt.mean() << "\t" << evt.median() << endl;
	}
}

unsigned Measure::iterations (void) {
	return eventset.number_of_events() * repetitions;
}

void Measure::add_result(unsigned index, long long unsigned value){
	eventset.add_result(index, value);
}

EventSet Measure::get_eventset(void) const {
	return eventset;
}
