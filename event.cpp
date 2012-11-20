#include "event.hpp"

using namespace std;

Event::Event (char* nam, int ev) {
	name.append(nam);
	code = ev;
}

string Event::get_name (void) {
	return name;
}

int Event::get_code (void) {
	return code;
}

void Event::add (long long unsigned value) {
	acc(value);
}

long long unsigned Event::min (void) {
	return boost::accumulators::min(acc);
}

long long unsigned Event::mean (void) {
	return boost::accumulators::mean(acc);
}

long long unsigned Event::median (void) {
	return boost::accumulators::median(acc);
}
