#include "measure.hpp"

using namespace boost::accumulators;
using namespace std;

Measure::Measure (EventSet *es) {
	eventset = es;
	acc = new accumulator_set <long long unsigned, stats< STATISTICS > > [eventset->size()];
	event_number = 0;
}

// cada vez que se executa o par start stop mede um evento
// para ja so mede uma vez cada evento
bool Measure::start (void) {
	int retval;
	char *error;

	if (event_number <= eventset->size()) {
		retval = PAPI_start((*eventset)[event_number]);

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
	long long int counter_value;

	if (event_number <= eventset->size()) {
		retval = PAPI_stop((*eventset)[event_number], &counter_value);

		if (retval != PAPI_OK) {
			error = PAPI_strerror(retval);

			cerr << "PAL | Measure: error measuring event - " << error << endl;
			cerr << "PAL | Measure: skipping event." << endl;

			++event_number;
			return false;
		} else {
			acc[event_number++]((unsigned) counter_value);
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

	for (unsigned i = 0; i < (unsigned) eventset->size(); ++i) {
		cout << eventset->get_event(i).get_name() << "\t";
		cout << boost::accumulators::min(acc[i]) << "\t";
		cout << mean(acc[i]) << "\t" << median(acc[i]) << endl;
	}
}
