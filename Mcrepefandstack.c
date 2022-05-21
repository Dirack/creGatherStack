/* CRE gather build and stacking for CMP X Offset CRE trajectory and interpolated data cube given

This program searches for the closest trace to the CRE trajectory to build the CRE Gather for each (m, h) pair given in the interpolated data cube, so sampling afects the result.

Programmer: Rodolfo A. C. Neves (Dirack) 07/03/2022

Email:  rodolfo_profissional@hotmail.com  

License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <rsf.h>
#include "pefInterpolation_lib.h"

int main(int argc, char* argv[])
{

	float*** t; // Data cube A(m,h,t)
	float** creGather; // CRE Gather
	float** stackedSection; // Stacked Section
	float ***creTimeCurve; // CRE traveltime curves
	float** m; // CMPs
	bool verb; // Verbose parameters
	float dm; // CMP sampling
	float om; // CMP axis origin
	int nm; // Number of CMP samples
	float dh; // Offset sampling
	float oh; // Offset axis origin
	int nh; // Offset number of samples
	float dt; // Time sampling
	float ot; // Time axis origin
	int nt; // Number of time samples
	int i,j,it0,im0; // loop counter
	int cn1; // Number of traces in CRE vector
	float cd1; // CRE Gather sampling
	float co1; // CRE Gather axis origin
	int cn2; // Number of m0s x t0s pairs
	int left_m; // CMP sample index
	int right_m;
	int aperture; // Number of traces in CRE Gather
	float mMax; // maximum CMP coordinate of the model
	float mMin; // maximum CMP coordinate of the model
	int nm0; // Number of m0s
	float om0; // m0's origin
	float dm0; // m0's sampling
	int nt0; // Number of t0s
	float ot0; // t0's origin
	float dt0; // t0's sampling
	int nht; // Number of offsets
	float dht; // Offsets sampling
	float oht; // Offsets axis origin
	float sumAmplitudes; // Amplitudes sum
	int tetai; // Time sample index
	float **trace;

	/* RSF files I/O */  
	sf_file in, out, timeCurves, cremh;

	/* RSF files axis */
	sf_axis ax,ay,az;

	sf_init(argc,argv);

	in = sf_input("in"); // Data cube A(m,h,t)
	cremh = sf_input("cremh"); /* CRE Gather m(h) coordinates */
	timeCurves = sf_input("timeCurves"); /* CRE time curves */
	out = sf_output("out"); // Stacked Section

	/* seismic data cube A(m,h,t) */
	if (!sf_histint(in,"n1",&nt)) sf_error("No n1= in input file");
	if (!sf_histfloat(in,"d1",&dt)) sf_error("No d1= in input file");
	if (!sf_histfloat(in,"o1",&ot)) sf_error("No o1= in input file");
	if (!sf_histint(in,"n2",&nh)) sf_error("No n2= in input file");
	if (!sf_histfloat(in,"d2",&dh)) sf_error("No d2= in input file");
	if (!sf_histfloat(in,"o2",&oh)) sf_error("No o2= in input file");
	if (!sf_histint(in,"n3",&nm)) sf_error("No n3= in input file");
	if (!sf_histfloat(in,"d3",&dm)) sf_error("No d3= in input file");
	if (!sf_histfloat(in,"o3",&om)) sf_error("No o3= in input file");

	/* cre trajectories m(h) */
	if(!sf_histint(cremh,"n1",&cn1)) sf_error("No n1= in cremh file");
	if(!sf_histfloat(cremh,"d1",&cd1)) sf_error("No d1= in cremh file");
	if(!sf_histfloat(cremh,"o1",&co1)) sf_error("No o1= in cremh file");
	if(!sf_histint(cremh,"n2",&cn2)) sf_error("No n2= in cremh file");

	/* Read cre time curves geometry */
	if (!sf_histint(timeCurves,"n1",&nht)) sf_error("No n1= in timeCurves input");
	if (!sf_histfloat(timeCurves,"d1",&dht)) sf_error("No d1= in timeCurves input");
	if (!sf_histfloat(timeCurves,"o1",&oht)) sf_error("No o1= in timeCurves input");
	if (!sf_histint(timeCurves,"n2",&nt0)) sf_error("No n2= in timeCurves input");
	if (!sf_histfloat(timeCurves,"d2",&dt0)) sf_error("No d2= timeCurves in input");
	if (!sf_histfloat(timeCurves,"o2",&ot0)) sf_error("No o2= timeCurves in input");
	if (!sf_histint(timeCurves,"n3",&nm0)) sf_error("No n3= in timeCurves input");
	if (!sf_histfloat(timeCurves,"d3",&dm0)) sf_error("No d3= in timeCurves input");
	if (!sf_histfloat(timeCurves,"o3",&om0)) sf_error("No o3= in timeCurves input");

	if(!sf_getint("aperture",&aperture)) aperture=1;
	/* Number of traces to put in a CRE Gather*/

	if(aperture > cn1){
		sf_error("The aperture can't be > n1 in cremh file\naperture=%i n2=%i",aperture,cn1);
	}

	if(! sf_getbool("verb",&verb)) verb=0;
	/* 1: active mode; 0: quiet mode */

	if (verb) {

		sf_warning("Active mode on!!!");
		sf_warning("CRE gather coordinates m(h) (cremh file): ");
		sf_warning("n1=%d d1=%f o1=%f",cn1,cd1,co1);
		sf_warning("n2=%d",cn2);
		sf_warning("CRE time curves: ");
		sf_warning("n1=%d d1=%f o1=%f",nht,dht,oht);
		sf_warning("n2=%d d2=%f o2=%f",nt0,dt0,ot0);
		sf_warning("n3=%d d3=%f o3=%f",nm0,dm0,om0);
		sf_warning("Input file dimensions: ");
		sf_warning("n1=%d d1=%f o1=%f",nt,dt,ot);
		sf_warning("n2=%d d2=%f o2=%f",nh,dh,oh);
		sf_warning("n3=%d d3=%f o3=%f",nm,dm,om);
	}

	/* Read CRE time curves */
	creTimeCurve = sf_floatalloc3(nht,nt0,nm0);
	sf_floatread(creTimeCurve[0][0],nm0*nt0*nht,timeCurves);

	/* Read data cube */
	t=sf_floatalloc3(nt,nh,nm);
	sf_floatread(t[0][0],nh*nm*nt,in);

	/* Read cre trajectories */	
	m = sf_floatalloc2(cn1,cn2);
	sf_floatread(m[0],cn1*cn2,cremh);
	creGather = sf_floatalloc2(nt,aperture);
	stackedSection = sf_floatalloc2(nt0,nm0);
	trace = sf_floatalloc2(nt,3);

	mMax = om+dm*nm;
	mMin = om;
	
	for(im0=0;im0<nm0;im0++){

		for(it0=0;it0<nt0;it0++){

			/* Generate CRE Gather for (t0,m0) pair */
			for(i=0;i<aperture;i++){
				left_m = (int)floor((double)m[(im0*nt0)+it0][i]/dm);
				right_m = (int)ceil((double)m[(im0*nt0)+it0][i]/dm);

				if(m[(im0*nt0)+it0][i] > mMax && m[(im0*nt0)+it0][i] < mMin){
					for(j=0;j<nt;j++)
						creGather[i][j] = 0.;
				}else{
					for(j=0;j<nt;j++){
						trace[0][j]=t[left_m][i][j];
						trace[1][j]=0.;
						trace[2][j]=t[right_m][i][j];
					}
					pefInterpolation(trace,nt);
					apef(trace,nt);
					for(j=0;j<nt;j++)
						creGather[i][j] = trace[1][j];
				}
				sf_warning("it0=%d im0=%d h=%d;",it0,im0,i);
			}

			/* CRE STACKING */	

			sumAmplitudes = 0;

			for(i=0; i < aperture; i++){
				/* Amplitude interpolation */
				tetai = (int) ((double)creTimeCurve[im0][it0][i]/dt);
				sumAmplitudes += creGather[i][tetai];
			} /* loop over h*/

			stackedSection[im0][it0] = sumAmplitudes;

		}/* loop over t0 */

	}/* loop over m0 */

	/* axis = sf_maxa(n,o,d)*/
	ax = sf_maxa(nt0, ot0, dt0);
	ay = sf_maxa(nm0, om0, dm0);
	az = sf_maxa(1, 0, 1);

	/* sf_oaxa(file, axis, axis index) */
	sf_oaxa(out,ax,1);
	sf_oaxa(out,ay,2);
	sf_oaxa(out,az,3);
	sf_oaxa(out,az,4);
	sf_floatwrite(stackedSection[0],nt0*nm0,out);
}
