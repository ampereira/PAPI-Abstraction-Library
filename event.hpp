#ifndef EVENT
#define EVENT

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/median.hpp>

#include <string>
#include <vector>

#define STATISTICS tag::mean, tag::min, tag::median

using namespace boost::accumulators;

class Event {
	std::string name;
	int code;
	accumulator_set <long long unsigned, stats< STATISTICS > > acc;

public: 
	Event (char*, int);
	std::string get_name (void);
	int get_code (void);
	void add_result (long long unsigned);
	long long unsigned min (void);
	long long unsigned mean (void);
	long long unsigned median (void);
};

#endif
