/*
* Test_rnip2vrms.c (C)
* 
* Purpose: Test of the functions in the library of the program 'Mrnip2vrms.c'.
* 
* Site: https://dirack.github.io
* 
* Version 1.0
* 
* Programer: Rodolfo A C Neves (Dirack) 22/09/2020
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "Unity/unity.h"
#include "../rnip2vrms_lib.h"
#include <rsf.h>

void setUp(){};
void tearDown(){};

void test_calculateVrmsSectionForRnipVector(){

	float rnip[6]={1.,2.,3.,4.,5.,0.};
	int nm0=2,nt0=3;
	float ot0=0.3,om0=2,v0=1.5;
	float** vrmsSection = sf_floatalloc2(nt0,nm0);
	int i,j;
	float t0;
	float v[6]={3.16,1.35,1.19,6.32,2.13,0.};

	/* Test funtion for a set of rnip values */
	vrmsSection = calculateVrmsSectionForRnipVector(rnip,nt0,ot0,nm0,om0,v0);
	for(i=0;i<nm0;i++){
		for(j=0;j<nt0;j++){
			t0 = nt0*j+ot0;
			TEST_ASSERT_FLOAT_WITHIN(0.01,v[j+i*nt0],
			vrmsSection[i][j]);
			sf_warning("%f",sqrt((2*rnip[j+i*nt0]*v0)/t0));
		}
	}
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_calculateVrmsSectionForRnipVector);
	return UNITY_END();
}
