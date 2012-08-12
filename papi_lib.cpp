#include "papi_lib.h"

using namespace std;

int length_events;
int *length;
int *EventSet;
long long **values;

Name_Events **name_events;

/*
 *  CPU Counters
 */
unsigned long long totIns[THREADS];
unsigned long long totCyc[THREADS];
unsigned long long L1DCM[THREADS];
unsigned long long L1DCA[THREADS];
unsigned long long L2DCM[THREADS];
unsigned long long FpIns[THREADS];
unsigned long long BrIns[THREADS];
unsigned long long SrIns[THREADS];
unsigned long long LdIns[THREADS];
unsigned long long InsNoLdSr[THREADS];

/*
 *  Timers
 */
unsigned long long totalTime[THREADS];
unsigned long long startTime[THREADS];
unsigned long long stopTime[THREADS];

/*
 *  GPU Counters
 */
unsigned long long cudaL1LoadHit[THREADS];
unsigned long long cudaBranch[THREADS];
unsigned long long cudaDivergentBranch[THREADS];

/*
 *  Control Variables
 */
unsigned long long measurements, SWmeasurements;
unsigned MAX_THREADS, papiflag, firstwrite = 0;




public:





// tem overhead em OpenMP...
void start_stopwatch_usec(){
	int threadID;

#ifdef OMP
	threadID = omp_get_thread_num();
#else
	threadID = 0;
#endif

	startTime[threadID] = PAPI_get_real_usec();
}

// tem overhead em OpenMP...
unsigned long long stop_stopwatch_usec(){
	int threadID;

#ifdef OMP
	threadID = omp_get_thread_num();
#else
	threadID = 0;
#endif

	stopTime[threadID] = PAPI_get_real_usec();
	totalTime[threadID] += (stopTime[threadID] - startTime[threadID]);
	SWmeasurements++;

	return stopTime[threadID] - startTime[threadID];
}

void stopwatch_usec_print_to_file(const char *name){
	char *fichout = NULL;
	FILE *res;

	fichout = strdup(name);
	strcat(fichout, ".time");
	res = fopen(fichout, "a+");

	fprintf(res, "\n-=== Easy PAPI Framework ===-\n --- Average results ---\n");
	if(SWmeasurements == 1)
		fprintf(res, " %llu measurement done!\n\n", SWmeasurements);
	else
		fprintf(res, " %llu measurements done!\n\n", SWmeasurements);

	if(MAX_THREADS > 1){
		for(unsigned i = 0; i < MAX_THREADS; ++i){
			fprintf(res, "Thread %d measured: %llu usec\n", i, totalTime[i] / SWmeasurements);
		}
	}else{
		fprintf(res, "Region measured: %llu usec\n", totalTime[0] / SWmeasurements);
	}	

	fclose(res);
	SWmeasurements = 0;
	papi_init_totalTime();
}

void papi_init_totalTime(){
	for(unsigned i = 0; i < THREADS; ++i){
		totalTime[i] = 0;
	}
}

unsigned long long papi_counter_median(unsigned long long counter){
	return counter / measurements;
}

//// deprecated
unsigned long long papi_counter_sum(unsigned long long counter){
	return counter;
}

// it's assumed that only works with OpenMP
int papi_thread_support_init(unsigned long int (*handle)()){
#ifdef OMP
	#pragma omp private(length_events, length, EventSet, values)
	return PAPI_thread_init(handle);
#else
	return 0;
#endif
}

void papi_print_results_to_file(const char *name){
	char* fichout = NULL;
	unsigned long long aux[NUM_COUNTERS][THREADS];
	unsigned i;

	for(unsigned c1 = 0; c1 < NUM_COUNTERS; ++c1){
		for(unsigned c2 = 0; c2 < MAX_THREADS; ++c2){
			aux[c1][c2] = 0;
		}
	}

	unsigned long long cyc = 0;

	fichout = strdup(name);
	strcat(fichout, ".counters");

	FILE *res = fopen(fichout, "a+");
	
	for(i = 0; i < MAX_THREADS; ++i){
		switch(papiflag){
			case 0 : aux[0][i] = papi_counter_median(totIns[i]);
					 aux[4][i] = papi_counter_median(FpIns[i]); 
					 break;
			case 1 : aux[1][i] = papi_counter_median(L1DCM[i]);
					 aux[5][i] = papi_counter_sum(totCyc[i]);   
					 break;
			case 2 : aux[2][i] = papi_counter_median(L1DCA[i]); 
					 break;
			case 3 : aux[3][i] = papi_counter_median(L2DCM[i]); 
					 break;
			case 4 : aux[6][i] = papi_counter_median(BrIns[i]); 
					 break;
			case 5 : aux[7][i] = papi_counter_median(SrIns[i]); 
					 break;
			case 6 : aux[8][i] = papi_counter_median(LdIns[i]); 
					 break;
			case 7 : aux[9][i] = papi_counter_median(InsNoLdSr[i]); 
					 break;
			case 10: aux[10][i] = papi_counter_median(cudaL1LoadHit[i]); 
					 break;
			case 11: aux[11][i] = papi_counter_median(cudaBranch[i]); 
					 break;
			case 12: aux[12][i] = papi_counter_median(cudaDivergentBranch[i]); 
					 break;
		}
	}

	// choses the highest number of totCyc from all the 
	if(papiflag == 1)
		for(i = 0; i < MAX_THREADS; ++i){
			if(cyc < aux[5][i])
				cyc = aux[5][i];
		}

	if(!firstwrite){
		firstwrite++;
		//fprintf(res, "\n-=== Easy PAPI Framework ===-\n --- Average results ---\n");
		if(measurements == 1)
			fprintf(res, " %llu measurement done!\n", measurements);
		else
			fprintf(res, " %llu measurements done!\n", measurements);
	}

	for(i = 0; i < MAX_THREADS; ++i){
		switch(papiflag){
			case 0 : fprintf(res, "Tot Inst: %llu\n", aux[0][i]);
					 fprintf(res, "FP INS: %llu\n", aux[4][i]);
					 break;
			case 1 : fprintf(res, "L1 DCM: %llu\n", aux[1][i]); 
					 break;
			case 2 : fprintf(res, "L1 DCA: %llu\n", aux[2][i]); 
					 break;
			case 3 : fprintf(res, "L2 DCM: %llu\n", aux[3][i]); 
					 break;
			case 4 : fprintf(res, "BR INS: %llu\n", aux[6][i]); 
					 break;
			case 5 : fprintf(res, "SR INS: %llu\n", aux[7][i]); 
					 break;
			case 6 : fprintf(res, "LD INS: %llu\n", aux[8][i]); 
					 break;
			case 7 : fprintf(res, "Total INS - LD - SR: %llu\n", aux[9][i]); 
					 break;
			case 10 : fprintf(res, "CUDA L1 local load hit: %llu\n", aux[10][i]); 
					 break;
			case 11 : fprintf(res, "CUDA Branches: %llu\n", aux[11][i]); 
					 break;
			case 12 : fprintf(res, "CUDA Divergent Branches: %llu\n", aux[12][i]); 
					 break;
		}
	}

	if(papiflag == 1)
		fprintf(res, "TOT CYC (longest thread): %llu\n", cyc);

	fclose(res);

	papi_init_counter_arrays();
	free(length);
	free(EventSet);
	free(values);
	measurements = 0;
}

void papi_init_counter_arrays(void){
	for(int i = 0; i < THREADS; ++i){
		totIns[i] = 0;
		totCyc[i] = 0;
		L1DCM[i]  = 0;
		L1DCA[i]  = 0;
		L2DCM[i]  = 0;
		FpIns[i]  = 0;
		BrIns[i]  = 0;
		SrIns[i]  = 0;
		LdIns[i]  = 0;
		InsNoLdSr[i]  = 0;
		cudaL1LoadHit[i] = 0;
		cudaBranch[i] = 0;
		cudaDivergentBranch[i] = 0;
	}
}

int create_events(Name_Events ***name_events2, int *length_events2, int **length2,
		int **EventSet2, long long *** values2, int var) ;

void papi_private_init(int var){
	papiflag = var;
	create_events(&name_events, &length_events, &length, &EventSet, &values, papiflag);
}

void papi_store_counters() {
	int threadID;

#ifdef OMP
	threadID = omp_get_thread_num();
#else
	threadID = 0;
#endif

	for (int i = 0; i < length_events; ++i) {
		switch(papiflag){
			case 0 : FpIns[threadID] += values[i][0]; 
					 totIns[threadID] += values[i][1];
					 values[i][0] = 0; 
					 values[i][1] = 0;
					 break;
			case 1 : totCyc[threadID] += values[i][0]; 
					 L1DCM[threadID] += values[i][1];
					 values[i][0] = 0; 
					 values[i][1] = 0;
					 break;
			case 2 : L1DCA[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
			case 3 : L2DCM[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
			case 4 : BrIns[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
			case 5 : SrIns[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
			case 6 : LdIns[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
			case 7 : InsNoLdSr[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
			case 10: cudaL1LoadHit[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
			case 11: cudaBranch[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
			case 12: cudaDivergentBranch[threadID] += values[i][0];
					 values[i][0] = 0; 
					 break;
		}
	}
}

int papi_init () {

	//init PAPI
	if ((PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT) {
		printf("PAPI library initialization error! \n");
		return 0;
	}

#ifdef OMP
	MAX_THREADS = omp_get_num_threads();
#else
	MAX_THREADS = 1;
#endif

	measurements = 0;
	SWmeasurements = 0;
	papi_init_counter_arrays();
	papi_init_totalTime();

	return 1;
}

void papi_finalize(void) {
	PAPI_cleanup_eventset(*EventSet);
  PAPI_shutdown();
}

void papi_start_event () {
	int retval, threadID;
	
#ifdef OMP
	threadID = omp_get_thread_num();
#else
	threadID = 0;
#endif

	Name_Events **aux = name_events;
	*EventSet = PAPI_NULL;
	if ((retval = PAPI_create_eventset((EventSet))) != PAPI_OK)
		ERROR_RETURN(retval);

	for (int j = 0; j < length[threadID]; ++j) {
		if ((retval = PAPI_add_event(*EventSet,
						aux[threadID][j]->valor)) != PAPI_OK)
			ERROR_RETURN(retval);
	}

	if ((retval = PAPI_start(*EventSet)) != PAPI_OK)
		ERROR_RETURN(retval);
}

void papi_stop_event () {
	int retval, threadID;

#ifdef OMP
	threadID = omp_get_thread_num();
#else
	threadID = 0;
#endif
	
	if ((retval = PAPI_stop(*EventSet, values[threadID])) != PAPI_OK) {
		ERROR_RETURN(retval);
	}else{
		measurements++;
		papi_store_counters();
	}
	//PAPI_cleanup_eventset(*EventSet);
}


// creates the events one wants to measure
// returns the number of such events, or better, the nbr of times 
// the code being measured has to be repeated to measure all events
int create_events(Name_Events ***name_events2, int *length_events2, int **length2,
		int **EventSet2, long long *** values2, int var) {

	Name_Events **aux_name_events;

	*length_events2 = 1;

	*length2 = (int*) malloc(sizeof(int) * *length_events2);
	*EventSet2 = (int*) malloc(sizeof(int) * *length_events2);

	if(var < 2){
		(*length2)[0] = 2;
	}else{
		(*length2)[0]= 1;
	}

	//Allocate arrays
	aux_name_events = (Name_Events**) malloc(sizeof(Name_Events*) **length_events2);
	*values2 = ( long long **) malloc(sizeof(long long *) **length_events2);

	for (int i = 0; i < (*length_events2); i++) {
		(*values2)[i] = (long long *) malloc(sizeof( long long) * (*length2)[i]);
		aux_name_events[i] = (Name_Events*) malloc(sizeof(Name_Events) * (*length2)[i]);

		for (int j = 0; j < (*length2)[i]; j++) {
			aux_name_events[i][j] = (Name_Events) malloc(sizeof(Valor_Name_Events));
		}
	}
	
	int ev = -1;

	switch(var){
		case 0 : aux_name_events[0][0]->name = strdup("PAPI_FP_INS");
				 aux_name_events[0][0]->valor = PAPI_FP_INS;
				 aux_name_events[0][1]->name = strdup("PAPI_TOT_INS");
				 aux_name_events[0][1]->valor = PAPI_TOT_INS;
				 break;
		case 1 : aux_name_events[0][1]->name = strdup("PAPI_L1_DCM");
				 aux_name_events[0][1]->valor = PAPI_L1_DCM;
				 aux_name_events[0][0]->name = strdup("PAPI_TOT_CYC");
				 aux_name_events[0][0]->valor = PAPI_TOT_CYC;
				 break;
		case 2 : aux_name_events[0][0]->name = strdup("PAPI_L1_DCA");
				 aux_name_events[0][0]->valor = PAPI_L1_DCA;
				 break;
		case 3 : aux_name_events[0][0]->name = strdup("PAPI_L2_DCM");
				 aux_name_events[0][0]->valor = PAPI_L2_DCM;
 				 break;
		case 4 : aux_name_events[0][0]->name = strdup("PAPI_BR_INS");
				 aux_name_events[0][0]->valor = PAPI_BR_INS;
 				 break;
		case 5 : aux_name_events[0][0]->name = strdup("PAPI_SR_INS");
				 aux_name_events[0][0]->valor = PAPI_SR_INS;
 				 break;
		case 6 : aux_name_events[0][0]->name = strdup("PAPI_LD_INS");
				 aux_name_events[0][0]->valor = PAPI_LD_INS;
 				 break;
		case 7 : aux_name_events[0][0]->name = strdup("INST_RETIRED:OTHER");
				 PAPI_event_name_to_code(aux_name_events[0][0]->name, &ev);
				 aux_name_events[0][0]->valor = ev;
 				 break;
		case 10: aux_name_events[0][0]->name = strdup("CUDA.Tesla_M2070.domain_a.l1_local_load_hit");
				 PAPI_event_name_to_code(aux_name_events[0][0]->name, &ev);
				 aux_name_events[0][0]->valor = ev;
				 break;
		case 11: aux_name_events[0][0]->name = strdup("CUDA.Tesla_M2070.domain_d.branch");
				 PAPI_event_name_to_code(aux_name_events[0][0]->name, &ev);
				 aux_name_events[0][0]->valor = ev;
				 break;
		case 12: aux_name_events[0][0]->name = strdup("CUDA.Tesla_M2070.domain_d.divergent_branch");
				 PAPI_event_name_to_code(aux_name_events[0][0]->name, &ev);
				 aux_name_events[0][0]->valor = ev;
				 break;
	}
	    
	*name_events2 = aux_name_events;

	return (*length_events2);
}

bool PAL::create_events (std::vector< string > evts) {
	int size = evts.size(), retval, index = 0;
	vector< int > event_codes (size);
	char error[PAPI_MAX_STR_LEN];
	bool conflict = false;

	// Creates the counters from their names
	for (vector< string >::iterator it = evts.begin(); it < evts.end(); ++it) {
		int ev;
		retval = PAPI_event_name_to_code (*it, &ev);

		if (retval != PAPI_OK) {
			PAPI_perror(retval, error, PAPI_MAX_STR_LEN);

			cerr << "PAL | error on counter " << *it << " - " << error << endl;
			cerr << "PAL | counter will not be added to the measurements." << endl;
		} else {
			event_codes.push_back(ev);
		}
	}

	// Creates the eventsets from the counters - tries to group compatible counters
	for (vector< int >::iterator it = event_codes.begin(); it < event_codes.end(); ++it) {
		if (eventset.size() == 0 || conflict){
			eventset.push_back(-1);
			retval = PAPI_create_eventset(&eventset.back());

			if (conflict)
				conflict = false;
		}
		if (retval != PAPI_OK) {
			PAPI_perror(retval, error, PAPI_MAX_STR_LEN);

			cerr << "PAL | could not create eventset - " << error << endl;
			cerr << "PAL | library will exit." << endl;

			return false;
		}

		retval = PAPI_add_event(it->c_str());

		switch (retval) {
			case PAPI_OK 	  : break;
			case PAPI_ECNFLCT : conflict = true; break;
			default : cerr << "PAL | error adding counter to eventset - " << error << endl;
					  cerr << "PAL | library will exit." << endl;
					  return false;
		}
	}
}
