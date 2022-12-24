/*
* rnip2vnmo_lib.c (C)
* 
* Purpose: Function's Library of Mrnip2vrms.c
* 
* Site: https://dirack.github.io
* 
* Programer: Rodolfo A C Neves (Dirack) 22/09/2020
* 
* Email: rodolfo_profissional@hotmail.com
* 
* License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

//#define LOGGING 1 /*< Comment/uncomment this line to use/not use logging option >*/
#include <stdlib.h>
#include <math.h>
#include <rsf.h>
/*^*/

float** calculateVnmoSectionForRnipVector( float** rnip, /* Vector rnip, nm0*nt0 dimension */
					   float** beta, /* Vector beta, nm0*nt0 dimension */
		    			   int nt0, /* Number of time samples */
		    			   float ot0, /* Time axis origin */
		    			   float dt0, /* Time sampling */
		    			   int nm0, /* Number of CMP samples */
		    			   float v0 /* Near surface velocity */
){
/*< Return the VRMS section for a RNIP vector given >*/
	float** vnmoSection;
	int i, j;
	float t0;

	vnmoSection = sf_floatalloc2(nt0,nm0);

	for(j=0;j<nm0;j++){
		for(i=0;i<nt0;i++){

			/* Return 0 for negative values of rnip */
			if(rnip[j][i]<=0){
				vnmoSection[j][i]=0;
				continue;
			}

			t0 = dt0*i+ot0;
			vnmoSection[j][i]=sqrt((2*rnip[j][i]*v0)/(t0*cosf(beta[j][i])*cosf(beta[j][i])));
			#ifdef LOGGING
				sf_warning("vrms=%f rnip=%f v0=%f t0=%f dt0=%f ot0=%f nt0=%d nm0=%d",
						vnmoSection[j][i],
						rnip[j][i],
						v0,
						t0,
						dt0,
						ot0,
						nt0,
						nm0);
			#endif
		}
	}

	return vnmoSection;
}
