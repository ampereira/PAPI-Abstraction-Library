#include "event.hpp"

using namespace std;

Event::Event (char* nam, int ev) {
	name.append(nam);
	code = ev;
}
