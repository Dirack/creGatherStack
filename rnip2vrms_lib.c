/*
* rnip2vrms_lib.c (C)
* 
* Purpose: Function's Library of Mrnip2vrms.c
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

#include <stdlib.h>
#include <math.h>
#include <rsf.h>
/*^*/

float** calculateVrmsSectionForRnipVector( float* rnip, /* Vector rnip, nm0*nt0 dimension*/
		    			   int nt0, /* Number of time samples */
		    			   float ot0, /* Time axis origin */
		    			   int nm0, /* Number of CMPS samples */
		    			   float om0, /* CMPs axis origin */
		    			   float v0 /* Near surface velocity */
){
/*< Return the VRMS section for a RNIP vector given >*/
	float** vrmsSection;
	int i, j;
	float t0;

	vrmsSection = sf_floatalloc2(nt0,nm0);

	for(j=0;j<nm0;j++){
		for(i=0;i<nt0;i++){
			t0 = nt0*i+ot0;
			vrmsSection[j][i]=sqrt((2*rnip[(j*nt0)+i]*v0)/t0);
			sf_warning("rnip=%f vrms=%f t0=%f nt0=%d i=%d ot0=%d",rnip[j*nt0+i],vrmsSection[j][i],t0,nt0,i,ot0);
		}
	}

	return vrmsSection;
}
