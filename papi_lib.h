
#include <papi.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#define ERROR_RETURN(retval) { fprintf(stderr, "Error PAPI %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval); 

class PAL {
public:

	std::vector< int > eventset;


	bool create_events (std::vector< std::string > evts);

};