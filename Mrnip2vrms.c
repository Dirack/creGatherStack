/* Version 1.0 - Estimate root mean square velocity (VRMS) from RNIP

more text

 Programer: Rodolfo A C Neves (Dirack) 21/09/2020
 
 Email: rodolfo_profissional@hotmail.com
 
 License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

#include <rsf.h>
/*^*/

int main(int argc,char* argv[]){
	
	bool verb;
	int nt0;
	float dt0;
	float ot0;
	int nm0;
	float dm0;
	float om0;
	int nrnip;

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
	
	if(verb){
		sf_warning("Input file (Stacked Section)");
		sf_warning("nt0=%f dt0=%f ot0=%f",nt0,dt0,ot0);
		sf_warning("nm0=%f dm0=%f ot0=%f",nm0,dm0,om0);
		sf_warning("RNIP's file");
		sf_warning("n1=%f",nrnip);
	}

	/* Calculate VRMS from RNIP */

	/* Output the VRMS section */

}
