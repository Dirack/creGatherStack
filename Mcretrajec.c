/* Version 1.0 - Calculate CRE trajectory on m,h plane given zero offset CRS parameters (RNIP, BETA)

Programer: Rodolfo A. C. Neves (Dirack) 31/08/2019

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
	float h; // Half offset
	float alpha; // Assymetry parameter
	float m0; // central CMP
	float* p; // RNIP and BETA parameters temporary vector
	float RNIP; 
	float BETA;
	int np; // Number of parameters
	bool verb;
	float dm; // CMP sampling
	float om; // CMP axis origin
	int nm; // Number of CMP samples
	float dh; // Half offset sampling
	float oh; // Half offset axis origin
	int nh; // Number of Half offset samples
	float dt; // Time sampling
	float ot; // Time axis origin
	int nt; // Number of time samples
	int i; // counter

	/* RSF files I/O */  
	sf_file in, out, par;

	/* RSF files axis */
	sf_axis ax,ay,az;

	sf_init(argc,argv);

	in = sf_input("in"); // Data cube A(m,h,t)
	par = sf_input("param"); // RNIP and BETA parameters
	out = sf_output("out"); // m(h) vector

	if (!sf_getfloat("m0",&m0)) m0=0;
	/* central CMP (Km) */

	if (!sf_histint(par,"n1",&np)){
		sf_error("No n1= in parameters file");
	}else if(np != 2){
		sf_error("The number of paramters should be 2: RNIP and BETA");
	}else{
		p = sf_floatalloc(2);
		sf_floatread(p,2,par);
		RNIP = p[0];
		if(RNIP == 0) sf_error("RNIP can't be zero");
		BETA = p[1];
	}

	if (!sf_histint(in,"n1",&nt)) sf_error("No n1= in input file");
	if (!sf_histfloat(in,"d1",&dt)) sf_error("No d1= in input file");
	if (!sf_histfloat(in,"o1",&ot)) sf_error("No o1= in input file");
	if (!sf_histint(in,"n2",&nh)) sf_error("No n2= in input file");
	if (!sf_histfloat(in,"d2",&dh)) sf_error("No d2= in input file");
	if (!sf_histfloat(in,"o2",&oh)) sf_error("No o2= in input file");
	if (!sf_histint(in,"n3",&nm)) sf_error("No n3= in input file");
	if (!sf_histfloat(in,"d3",&dm)) sf_error("No d3= in input file");
	if (!sf_histfloat(in,"o3",&om)) sf_error("No o3= in input file");

	if(! sf_getbool("verb",&verb)) verb=0;
	/* 1: active mode; 0: quiet mode */

	alpha = sin(BETA)/RNIP;

	if (verb) {

		sf_warning("Active mode on!!!");
		sf_warning("Command line parameters: "); 
		sf_warning("m0=%f",m0);
		sf_warning("Input file parameters: ");
		sf_warning("RNIP=%f BETA=%f",RNIP,BETA);
		sf_warning("Data cube dimensions: ");
		sf_warning("n1=%i d1=%f o1=%f",nt,dt,ot);
		sf_warning("n2=%i d2=%f o2=%f",nh,dh,oh);
		sf_warning("n3=%i d3=%f o3=%f",nm,dm,om);
		sf_warning("Calculated assimetry parameter:");
		sf_warning("alpha=%f", alpha);
	}
	
	m = sf_floatalloc(nh);

	if(alpha <= 0.001){
		for(i=0;i<nh;i++){
			m[i] = m0;
		}
	}else{
		for(i=0;i<nh;i++){
			h = (dh*i) + oh;
			m[i] = m0 + (1/(2*alpha)) * (1 - sqrt(1 + 4 * alpha * alpha * h * h));
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
	sf_floatwrite(m,nh,out);

	exit(0);
}
