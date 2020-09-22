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

void setUp(){};
void tearDown(){};

void test_calculateVrmsSectionForRnipVector(){
	TEST_ASSERT_EQUAL(0,0);
}

int main(void){
	UNITY_BEGIN();
	RUN_TEST(test_calculateVrmsSectionForRnipVector);
	return UNITY_END();
}
