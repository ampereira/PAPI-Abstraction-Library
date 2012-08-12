
#include <papi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#ifdef OMP
    #include <omp.h>
#endif

#define ERROR_RETURN(retval) { fprintf(stderr, "Error PAPI %d %s:line %d: \n", retval,__FILE__,__LINE__);  exit(retval); }

#define THREADS 24
#define NUM_COUNTERS 13

typedef struct struct_name_events { 
    char* name; 
    int valor; 
}*Name_Events, Valor_Name_Events;

class PAL {

	int papi_thread_support_init(unsigned long int (*handle)());
	void papi_print_results_to_file(const char*);
	unsigned long long papi_counter_sum(unsigned long long);
	unsigned long long papi_counter_median(unsigned long long);
	void papi_init_counter_arrays(void);
	void papi_store_counters(void);
	int papi_init (void);
	void papi_private_init(int);
	void papi_finalize(void);
	void papi_start_event (void);
	void papi_stop_event (void);
	void start_stopwatch_usec(void);
	unsigned long long stop_stopwatch_usec(void);
	void stopwatch_usec_print_to_file(const char*);
	void papi_init_totalTime(void);

	std::vector< int > eventset;

public:

	bool create_events (std::vector< string >);

};