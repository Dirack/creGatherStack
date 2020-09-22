/* Version 1.0 - Estimate root mean square velocity (VRMS) from RNIP

 This program is based on multifocus formula that allows to estimate
 VRMS from RNIP: vrms = sqrt(2*RNIP*v0/t0)

 Reference: Diffraction imaging by multifocusing, Berkovitch A.,
 Belfer I., Hassin Y., and Landa E., 2009.

 Programer: Rodolfo A C Neves (Dirack) 21/09/2020
 
 Email: rodolfo_profissional@hotmail.com
 
 License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include "rnip2vrms_lib.h"
#include <rsf.h>
/*^*/

int main(int argc,char* argv[]){
	
	bool verb; // Verbose parameter
	int nt0; // Number of t0's in stacked section
	float dt0; // Time sampling in stacked section
	float ot0; // Origin of the time axis in stacked section
	int nm0; // Number of CMP's in stacked section
	float dm0; // CMP sampling in stacked section
	float om0; // Origin of the CMP axis in stacked section
	int nrnip; // Number of samples in rnip vector
	float v0; // Near surface velocity
	float* rnip; // rnip vector
	float** vrmsSection; // VRMS Section (t0,m0,vrms)

	sf_file in,rnip_file,out;
	sf_init(argc,argv);

	in = sf_input("in");
	rnip_file = sf_input("rnip");
	out = sf_output("out");

	/* Read coordinates of the stacked section file */
	if(!sf_histint(in,"n1",&nt0)) sf_error("No n1= in input");
	if(!sf_histfloat(in,"d1",&dt0)) sf_error("No d1= in input");
	if(!sf_histfloat(in,"o1",&ot0)) sf_error("No o1= in input");
	if(!sf_histint(in,"n2",&nm0)) sf_error("No n2= in input");
	if(!sf_histfloat(in,"d2",&dm0)) sf_error("No d2= in input");
	if(!sf_histfloat(in,"o2",&om0)) sf_error("No o2= in input");

	/* Read the coordinates of RNIP values file */
	if(!sf_histint(rnip_file,"n1",&nrnip)) sf_error("No n1= in rnips file");

	if(!sf_getbool("verb",&verb)) verb=0;
	/*1: verbose; 0: quiet*/

	if(!sf_getfloat("v0",&v0)) v0=1.5;
	/* Near surface velocity (Km/s) */
	
	if(verb){
		sf_warning("Input file (Stacked Section)");
		sf_warning("nt0=%f dt0=%f ot0=%f",nt0,dt0,ot0);
		sf_warning("nm0=%f dm0=%f ot0=%f",nm0,dm0,om0);
		sf_warning("RNIP's file");
		sf_warning("n1=%f",nrnip);
		sf_warning("Command line parameters");
		sf_warning("v0=%f",v0);
	}

	/* Assure that each (t0,m0) pair has a rnip value */
	if(!((nm0*nt0)==nrnip))
	sf_error("Dimension n1 of rnip vector should be equal n1*n2 in stacked section");

	/* Load rnip values */
	rnip = sf_floatalloc(nm0*nt0);
	sf_floatread(rnip,nm0*nt0,rnip_file);
	vrmsSection = sf_floatalloc2(nt0,nm0);

	/* Calculate VRMS from RNIP */
	vrmsSection = calculateVrmsSectionForRnipVector(rnip,nm0,nt0,om0,ot0,v0);

	/* Output the VRMS section */
	sf_floatwrite(vrmsSection[0],nt0*nm0,out);
}
