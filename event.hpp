#ifndef EVENT
#define EVENT

#include <string>
#include <vector>

class Event {
	std::string name;
	int code;

public: 
	Event (char*, int);
	std::string get_name (void);
	int get_code (void);
};

#endif
