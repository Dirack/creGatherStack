/* Calculate CRE traveltime curve t(m,h) given CRS zero-offset parameters (RN, RNIP, BETA)

Programmer: Rodolfo A. C. Neves (Dirack) 14/09/2019

Email:  rodolfo_profissional@hotmail.com 

License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>. 

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <rsf.h>

int main(int argc, char* argv[])
{

	float** m; // CMP
	float** t; // CRE traveltime curve
	float h; // Half offset
	double alpha; // Assymetry parameter
	float m0; // m0 coordinate
	float t0; // t0 coordinate
	int nm0; // central CMP
	float om0; // m0s axis origin
	float dm0; // m0s sampling
	float v0; // Near surface velocity
	int nt0; // Normal ray traveltime
	float ot0; // t0s axis origin
	float dt0; // t0s sampling
	int ni; // Number of m0s x t0s pairs
	float*** p; // RNIP and BETA temporary vector
	int np; // Number of parameters
	bool verb; // Verbose
	float dh; // Half offset sampling
	float oh; // Half offset axis origin
	int nh; // Half offset number of samples
	int i,l,k; // loop counter
	double c1, c2; // temporary variables of CRE approximation
	double d; // Distance to the central CMP m0
        double a1, a2, b2, b1, Fd, Fd1, Fd2; // temporary variables of CRS approximation
	bool cds; // Choose the traveltime approximation CRE or CRS

	/* RSF files I/O */  
	sf_file in, out, par;

	/* RSF files axis */
	sf_axis ax,ay,az;

	sf_init(argc,argv);

	in = sf_input("in"); // m(h) vector (CRE coordinates)
	par = sf_input("param"); // CRS parameters (RNIP, BETA)
	out = sf_output("out"); // CRE traveltime curve t(m,h)

	if (!sf_getfloat("v0",&v0)) v0=1.5;
	/* Near surface velocity (Km/s) */

	/* Parameters file */
	if (!sf_histint(par,"n1",&nt0)) sf_error("No n1= in parameters file");
	if (!sf_histfloat(par,"d1",&dt0)) sf_error("No d1= in parameters file");
	if (!sf_histfloat(par,"o1",&ot0)) sf_error("No o1= in parameters file");
	if (!sf_histint(par,"n2",&nm0)) sf_error("No n2= in parameters file");
	if (!sf_histfloat(par,"d2",&dm0)) sf_error("No d2= in parameters file");
	if (!sf_histfloat(par,"o2",&om0)) sf_error("No o2= in parameters file");
	if (!sf_histint(par,"n3",&np)) sf_error("No n3= in parameters file");

	/* m(h) coordinates */
	if (!sf_histint(in,"n1",&nh)) sf_error("No n1= in input file");
	if (!sf_histfloat(in,"d1",&dh)) sf_error("No d1= in input file");
	if (!sf_histfloat(in,"o1",&oh)) sf_error("No o1= in input file");
	if (!sf_histint(in,"n2",&ni)) sf_error("No n2= in input file");

	/* Check input dimensions */
	if ((nt0*nm0) != ni)
		sf_error("n2 in input should be equal to n1*n2 in parameters file");
	if(np < 3)
		sf_error("Number of parameters should be at least 3 in the input file: RN, RNIP and BETA");

	if(! sf_getbool("verb",&verb)) verb=0;
	/* 1: active mode; 0: quiet mode */

	if(! sf_getbool("cds",&cds)) cds=0;
	/* 1: Non-hyperbolic CRS using CDS condition; 0: cre approximation */

	if (verb) {

		sf_warning("Active mode on!!!");
		sf_warning("Parameters file: "); 
		sf_warning("nm0=%d om0=%f dm0=%f",nm0,om0,dm0);
		sf_warning("nt0=%d ot0=%f dt0=%f",nt0,ot0,dt0);
		sf_warning("n3=%d",np);
		sf_warning("Input file dimensions: ");
		sf_warning("n1=%d d1=%f o1=%f",nh,dh,oh);
		sf_warning("n2=%d",ni);
	}
	
	/* Read input and parameters */
	m = sf_floatalloc2(nh,ni);
	sf_floatread(m[0],nh*ni,in);
	p = sf_floatalloc3(nt0,nm0,np);
	sf_floatread(p[0][0],nt0*nm0*np,par);
	t = sf_floatalloc2(nh,ni);

	for(l=0;l<nm0;l++){

		m0 = dm0*l+om0;

		for(k=0;k<nt0;k++){

			t0 = dt0*k+ot0;

			if(!cds){
				alpha = sin(p[2][l][k])/p[1][l][k];
				/* CRE approximation */
				for(i=0;i<nh;i++){
					h = (dh*i) + oh;
					d = m[(l*nt0)+k][i]-m0;
					c1 = (d+h)/(p[1][l][k]);
					c2 = (d-h)/(p[1][l][k]);
					t[(l*nt0)+k][i] = (t0-2*p[1][l][k]/v0)+(p[1][l][k]/v0)*sqrt(1-2*alpha*(d+h)+c1*c1)+(p[1][l][k]/v0)*sqrt(1-2*alpha*(d-h)+c2*c2);
				}
			}else{
				/* Non-hyperbolic CRS approximation with CDS condition (RN=RNIP) */
				for(i=0;i<nh;i++){
					h = (dh*i) + oh;
					d = m[(l*nt0)+k][i]-m0;
					a1=(2*sin(p[2][l][k]))/(v0);
					a2=(2*cos(p[2][l][k])*cos(p[2][l][k])*t0)/(v0*p[1][l][k]);
					b2=(2*cos(p[2][l][k])*cos(p[2][l][k])*t0)/(v0*p[1][l][k]);
					b1=2*b2+a1*a1-a2;
					Fd=(t0+a1*d)*(t0+a1*d)+a2*d*d;
					Fd2=(t0+a1*(d-h))*(t0+a1*(d-h))+a2*(d-h)*(d-h);
					Fd1=(t0+a1*(d+h))*(t0+a1*(d+h))+a2*(d+h)*(d+h);
					t[(l*nt0)+k][i]=sqrt((Fd+b1*h*h+sqrt(Fd2*Fd1))*0.5);
				}
			}
		}/*loop over t0 */
	}/* loop over m0 */

	/* axis = sf_maxa(n,o,d)*/
	ax = sf_maxa(nh, oh, dh);
	ay = sf_maxa(nt0, ot0, dt0);
	az = sf_maxa(nm0, om0, dm0);

	/* sf_oaxa(file, axis, axis index) */
	sf_oaxa(out,ax,1);
	sf_oaxa(out,ay,2);
	sf_oaxa(out,az,3);

        sf_putstring(out,"label1","Offset");
        sf_putstring(out,"unit1","Km");
        sf_putstring(out,"label2","t0");
        sf_putstring(out,"unit2","s");
        sf_putstring(out,"label3","m0");
        sf_putstring(out,"unit3","Km");

	sf_floatwrite(t[0],nh*ni,out);
}
