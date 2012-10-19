#ifndef MEASURE
#define MEASURE

#include "eventset.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/median.hpp>

#define STATISTICS tag::mean, tag::min, tag::median

using namespace boost::accumulators;

class Measure {
	EventSet *eventset;
	accumulator_set <long long unsigned, stats< STATISTICS > > *acc;	// to hold the measurement data for each counter

public:
	Measure (EventSet*);
	bool start ();
	bool stop ();
};

#endif
