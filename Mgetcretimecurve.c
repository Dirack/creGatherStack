/* Version 1.0 - Calculate CRE traveltime curve t(m,h) given CRS zero offset parameters (RN, RNIP, BETA)

Programer: Rodolfo A. C. Neves (Dirack) 14/09/2019

Email:  rodolfo_profissional@hotmail.com 

License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>. 

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <rsf.h>

int main(int argc, char* argv[])
{

	float* m; // CMP
	float* t; // CRE traveltime curve
	float h; // Half offset
	double alpha; // Assymetry parameter
	float m0; // central CMP
	float v0; // Near surface velocity
	float t0; // Normal ray traveltime
	float* p; // RNIP and BETA temporary vector
	float RNIP; // RNIP - CRS parameter
	float BETA; // RN - CRS parameter
	int np; // Number of parameters
	bool verb; // Verbose
	float dh; // Half offset sampling
	float oh; // Half offset axis origin
	int nh; // Half offset number of samples
	int i; // loop counter
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

	if (!sf_getfloat("m0",&m0)) m0=0;
	/* central CMP (Km) */

	if (!sf_getfloat("v0",&v0)) v0=1.5;
	/* Near surface velocity (Km/s) */

	if (!sf_getfloat("t0",&t0)) t0=0;
	/* Normal ray traveltime (s) */

	if (!sf_histint(par,"n1",&np)){
		sf_error("No n1= in the parameter file");
	}else if(np < 3){
		sf_error("Number of parameters should be 3 at least in the input file: RN, RNIP and BETA");
	}else{
		p = sf_floatalloc(np);
		sf_floatread(p,np,par);
		RNIP = p[1];
		if(RNIP == 0) sf_error("RNIP can't be zero");
		BETA = p[2];
	}

	if (!sf_histint(in,"n1",&nh)) sf_error("No n1= in input file");
	if (!sf_histfloat(in,"d1",&dh)) sf_error("No d1= in input file");
	if (!sf_histfloat(in,"o1",&oh)) sf_error("No o1= in input file");

	if(! sf_getbool("verb",&verb)) verb=0;
	/* 1: active mode; 0: quiet mode */

	if(! sf_getbool("cds",&cds)) cds=0;
	/* 1: Non-hyperbolic CRS using CDS condition; 0: cre approximation */

	alpha = sin(BETA)/RNIP;

	if (verb) {

		sf_warning("Active mode on!!!");
		sf_warning("Command line parameters: "); 
		sf_warning("m0=%f t0=%f v0=%f",m0,t0,v0);
		sf_warning("CRS parameters: ");
		sf_warning("RNIP=%f BETA=%f",RNIP,BETA);
		sf_warning("Input file dimensions: ");
		sf_warning("n1=%i d1=%f o1=%f",nh,dh,oh);
		sf_warning("Assymetry parameter:");
		sf_warning("alpha=%f", alpha);
	}
	
	m = sf_floatalloc(nh);
	sf_floatread(m,nh,in);
	t = sf_floatalloc(nh);

	if(!cds){
		/* CRE approximation */
		for(i=0;i<nh;i++){
			h = (dh*i) + oh;
			c1 = (m[i]-m0+h)/(RNIP);
			c2 = (m[i]-m0-h)/(RNIP);
			t[i] = (t0-2*RNIP/v0)+(RNIP/v0)*sqrt(1-2*alpha*(m[i]-m0+h)+c1*c1)+(RNIP/v0)*sqrt(1-2*alpha*(m[i]-m0-h)+c2*c2);
		}
	}else{
		/* Non-hyperbolic CRS approximation with CDS condition (RN=RNIP) */
		for(i=0;i<nh;i++){
			h = (dh*i) + oh;
			d = m[i]-m0;
			a1=(2*sin(BETA))/(v0);
			a2=(2*cos(BETA)*cos(BETA)*t0)/(v0*RNIP);
			b2=(2*cos(BETA)*cos(BETA)*t0)/(v0*RNIP);
			b1=2*b2+a1*a1-a2;
			Fd=(t0+a1*d)*(t0+a1*d)+a2*d*d;
			Fd2=(t0+a1*(d-h))*(t0+a1*(d-h))+a2*(d-h)*(d-h);
			Fd1=(t0+a1*(d+h))*(t0+a1*(d+h))+a2*(d+h)*(d+h);
			t[i]=sqrt((Fd+b1*h*h+sqrt(Fd2*Fd1))*0.5);
		}
	}

	/* axis = sf_maxa(n,o,d)*/
	ax = sf_maxa(nh, oh, dh);
	ay = sf_maxa(1, 0, 1);
	az = sf_maxa(1, 0, 1);

	/* sf_oaxa(file, axis, axis index) */
	sf_oaxa(out,ax,1);
	sf_oaxa(out,ay,2);
	sf_oaxa(out,az,3);
	sf_floatwrite(t,nh,out);

	exit(0);
}
