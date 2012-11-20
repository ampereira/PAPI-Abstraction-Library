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
