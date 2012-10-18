#ifndef EVENT
#define EVENT

#include <string>
#include <vector>

class Event {
public: 
	static std::string name;
	static int code;

	Event (char*, int);
};

#endif
