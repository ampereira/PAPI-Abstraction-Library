#include "measure.hpp"

using namespace boost::accumulators;

Measure::Measure (EventSet *es) {
	eventset = es;
	acc = new accumulator_set <long long unsigned, stats< STATISTICS > > [eventset->size()];
}

// como tratar os varios eventos? possivel se nao se alterar os parametros de entrada da zona
// VER GOTO
bool Measure::start (void) {
	return false;
}

bool Measure::stop (void) {
	return false;
}
