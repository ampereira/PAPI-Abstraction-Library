
#include <papi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


int papi_thread_support_init(unsigned long int (*handle)());
void papi_print_results_to_file(const char *name);
unsigned long long papi_counter_sum(unsigned long long counter);
unsigned long long papi_counter_median(unsigned long long counter);
void papi_init_counter_arrays(void);
void papi_store_counters(void);
int papi_init (void);
void papi_private_init(int var);
void papi_finalize(void);
void papi_start_event (void);
void papi_stop_event (void);
void start_stopwatch_usec(void);
unsigned long long stop_stopwatch_usec(void);
void stopwatch_usec_print_to_file(const char *name);
void papi_init_totalTime(void);

