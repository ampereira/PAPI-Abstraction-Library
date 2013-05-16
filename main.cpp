#include "papi_lib.h"
#include <cstdlib>
#include <string>
using namespace std;

int main(void){
	PAL *pal = new PAL();

	vector< string > st;
	string st1 = "PAPI_TOT_CYC";
	string st2 = "PAPI_TOT_INS";
	string st3 = "PAPI_L2_DCM";

	st.push_back(st1);
	st.push_back(st2);
	st.push_back(st3);

	pal->create_events(st);

	return 0;
}