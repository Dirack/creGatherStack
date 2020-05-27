/* Version 1.0 - Build CRE gather given m,h CRE trajectory coordinates and interpolated data cube

This program searches for the closest trace for each m,h pair given in the interpolated data cube. 

Programer: Rodolfo A. C. Neves (Dirack) 04/09/2019

Email:  rodolfo_profissional@hotmail.com  

License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <rsf.h>

int main(int argc, char* argv[])
{

	float*** t; // Data cube A(m,h,t)
	float** creGather;
	float* m; // CMP
	bool verb;
	float dm; // CMP sampling
	float om; // CMP axis origin
	int nm; // Number of CMP samples
	float dh; // Offset sampling
	float oh; // Offset axis origin
	int nh; // Offset number of samples
	float dt; // Time sampling
	float ot; // Time axis origin
	int nt; // Number of time samples
	int i,j; // loop counter
	int cre_n; // Number of traces in CRE vector
	float cre_d; // CRE Gather sampling
	float cre_o; // CRE Gather axis origin
	int trac_m; // CMP sample index
	int aperture; // Number of traces in CRE Gather

	/* RSF files I/O */  
	sf_file in, out, out_m, cremh;

	/* RSF files axis */
	sf_axis ax,ay,az,am;

	sf_init(argc,argv);

	in = sf_input("in"); // Data cube A(m,h,t)
	cremh = sf_input("cremh"); /* CRE Gather m(h) coordinates */
	out = sf_output("out"); // CRE Gather
	out_m = sf_output("m"); // CRE Gather CMP coordinate

	if (!sf_histint(in,"n1",&nt)) sf_error("No n1= in input file");
	if (!sf_histfloat(in,"d1",&dt)) sf_error("No d1= in input file");
	if (!sf_histfloat(in,"o1",&ot)) sf_error("No o1= in input file");
	if (!sf_histint(in,"n2",&nh)) sf_error("No n2= in input file");
	if (!sf_histfloat(in,"d2",&dh)) sf_error("No d2= in input file");
	if (!sf_histfloat(in,"o2",&oh)) sf_error("No o2= in input file");
	if (!sf_histint(in,"n3",&nm)) sf_error("No n3= in input file");
	if (!sf_histfloat(in,"d3",&dm)) sf_error("No d3= in input file");
	if (!sf_histfloat(in,"o3",&om)) sf_error("No o3= in input file");

	if(!sf_histint(cremh,"n1",&cre_n)) sf_error("No n1= in cremh file");
	if(!sf_histfloat(cremh,"d1",&cre_d)) sf_error("No d1= in cremh file");
	if(!sf_histfloat(cremh,"o1",&cre_o)) sf_error("No o1= in cremh file");

	if(!sf_getint("aperture",&aperture)) aperture=1;
	/* Number of traces in a CRE Gather*/

	if(aperture > cre_n){
		sf_error("The aperture can't be > n1 in cremh file\naperture=%i n2=%i",aperture,cre_n);
	}

	if(! sf_getbool("verb",&verb)) verb=0;
	/* 1: active mode; 0: quiet mode */

	if (verb) {

		sf_warning("Active mode on!!!");
		sf_warning("CRE gather coordinates m(h) (cremh file): ");
		sf_warning("n1=%i d1=%f o1=%f",cre_n,cre_d,cre_o);
		sf_warning("Input file dimensions: ");
		sf_warning("n1=%i d1=%f o1=%f",nt,dt,ot);
		sf_warning("n2=%i d2=%f o2=%f",nh,dh,oh);
		sf_warning("n3=%i d3=%f o3=%f",nm,dm,om);
	}

	/* Read data cube */
	t=sf_floatalloc3(nt,nh,nm);
	sf_floatread(t[0][0],nh*nm*nt,in);
	
	m = sf_floatalloc(cre_n);
	sf_floatread(m,cre_n,cremh);
	creGather = sf_floatalloc2(nt,aperture);

	for(i=0;i<aperture;i++){
		trac_m = (int)((double)m[i]/dm);

		for(j=0;j<nt;j++){
			creGather[i][j] = t[trac_m][i][j];
		}
	}

	/* eixo = sf_maxa(n,o,d)*/
	ax = sf_maxa(nt, ot, dt);
	ay = sf_maxa(aperture, oh, dh);
	az = sf_maxa(1, 0, 1);

	/* sf_oaxa(arquivo, eixo, índice do eixo) */
	sf_oaxa(out,ax,1);
	sf_oaxa(out,ay,2);
	sf_oaxa(out,az,3);
	sf_floatwrite(creGather[0],aperture*nt,out);

	/* eixo do vetor m */
	am = sf_maxa(cre_n,oh,dh);
	sf_oaxa(out_m,am,1);
	sf_oaxa(out_m,az,2);
	sf_oaxa(out_m,az,3);
	sf_floatwrite(m,cre_n,out_m);

	exit(0);
}
