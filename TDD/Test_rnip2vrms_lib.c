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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define nm0 2
#define nt0 3
#define dt0 0.3
#define ot0 0.3
#define om0 2
#define v0 1.5

/* Table of values of rnip and vrms */
float rnip[]={1.,2.5,3.3,4.2,5.1,0.};
float** rnipSection;
const float v[]={3.16,3.53,3.31,6.48,5.05,0.};
float** vrmsSection;

float generateRandomNumberBetween0And1(){
	int u;
	float ur;

	u=rand()%100;
	ur=(float)u/100;

	return ur;
}

void setUp(){

	int i, j;

	vrmsSection = sf_floatalloc2(nt0,nm0);
	rnipSection = sf_floatalloc2(nt0,nm0);

	for(i=0;i<nm0;i++){
		for(j=0;j<nt0;j++){
			rnipSection[i][j]=rnip[j+i*nt0];
		}
	}
};
void tearDown(){};

void test_calculateVrmsSectionForRnipVector(){

	int i,j;

	/* Test funtion for a set of rnip values */
	vrmsSection = calculateVrmsSectionForRnipVector(rnipSection,nt0,ot0,dt0,om0,v0);
	for(i=0;i<nm0;i++){
		for(j=0;j<nt0;j++){
			TEST_ASSERT_FLOAT_WITHIN(0.01,v[j+i*nt0],
			vrmsSection[i][j]);
		}
	}
}

void test_negativeValues_calculateVrmsSectionForRnipVector(){
	int i,j;
	float t0;

	/* Generate negative rnip values */
	for(i=0;i<nm0;i++){
		for(j=0;j<nt0;j++){
			rnipSection[i][j]=-2.0+generateRandomNumberBetween0And1();
		}
	}

	/* Test funtion for a set of negative rnip values */
	vrmsSection = calculateVrmsSectionForRnipVector(rnipSection,nt0,ot0,dt0,om0,v0);
	for(i=0;i<nm0;i++){
		for(j=0;j<nt0;j++){
			t0 = dt0*j+ot0;
			TEST_ASSERT_FLOAT_WITHIN(0.01,0.0,
			vrmsSection[i][j]);
		}
	}
}

void test_randomNumbers_calculateVrmsSectionForRnipVector(){
	
	int i,j,k;
	float t0;
	srand(time(NULL));

	/* Repeat this test several times */
	for(k=0;k<100;k++){

		/* Generate random rnip values */
		for(i=0;i<nm0;i++){
			for(j=0;j<nt0;j++){
				rnipSection[i][j]=rnip[j+i*nt0]+generateRandomNumberBetween0And1();
			}
		}

		/* Test funtion for a set of random rnip values */
		vrmsSection = calculateVrmsSectionForRnipVector(rnipSection,nt0,ot0,dt0,om0,v0);
		for(i=0;i<nm0;i++){
			for(j=0;j<nt0;j++){
				t0 = dt0*j+ot0;
				TEST_ASSERT_FLOAT_WITHIN(0.01,sqrt(2*rnipSection[i][j]*v0/t0),
				vrmsSection[i][j]);
			}
		}
	} /* Loop over tests */
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_calculateVrmsSectionForRnipVector);
	RUN_TEST(test_randomNumbers_calculateVrmsSectionForRnipVector);
	RUN_TEST(test_negativeValues_calculateVrmsSectionForRnipVector);
	return UNITY_END();
}
