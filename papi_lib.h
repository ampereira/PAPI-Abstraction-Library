
#include <papi.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#define ERROR_RETURN(retval) { fprintf(stderr, "Error PAPI %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval);
#define MAX_COUNTERS 30 

class PAL {
public:

	int eventset [MAX_COUNTERS];
	int eventset_size = 0;

	bool create_events (std::vector< std::string >);

};