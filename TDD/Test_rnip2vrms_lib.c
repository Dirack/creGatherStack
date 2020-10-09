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
#define nm0 2
#define nt0 3
#define dt0 0.3
#define ot0 0.3
#define om0 2
#define v0 1.5

/* Table of values of rnip and vrms */
float rnip[]={1.,2.5,3.3,4.2,5.1,0.};
const float v[]={3.16,3.53,3.31,6.48,5.05,0.};
float** vrmsSection;

void setUp(){
	vrmsSection = sf_floatalloc2(nt0,nm0);
};
void tearDown(){};

void test_calculateVrmsSectionForRnipVector(){

	int i,j;
	float t0;

	/* Test funtion for a set of rnip values */
	vrmsSection = calculateVrmsSectionForRnipVector(rnip,nt0,ot0,dt0,om0,v0);
	for(i=0;i<nm0;i++){
		for(j=0;j<nt0;j++){
			t0 = nt0*j+ot0;
			TEST_ASSERT_FLOAT_WITHIN(0.01,v[j+i*nt0],
			vrmsSection[i][j]);
		}
	}
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_calculateVrmsSectionForRnipVector);
	return UNITY_END();
}
