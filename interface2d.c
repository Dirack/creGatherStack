/*
	 interface2d.c (c)
	 
	 Purpose: Model interface 2D interpolated with cubic splines.
	 	 
	 Version 1.0
	 
	 Site: https://dirack.github.io
	 
	 Programmer: Rodolfo A. C. Neves (Dirack) 25/12/2021

	 Email:  rodolfo_profissional@hotmail.com

	 License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

*/
#include <rsf.h>
#include "interface2d.h"

#ifndef _interface2d_h_

typedef struct Interface2d *itf2d;
/* abstract data type */
/*^*/

#endif

struct Interface2d{
	float *coef; // Cubic spline coefficients Matrix
	float *z; // Nodepoints z(x)
	int n; // Number of nodes
	float o; // Axis origin
	float d; // Nodes sampling
};
/* Concrete data type */

//TODO: correct "coefficients" in the function name
void calculateSplineCoeficients(int n, /* Vectors (x,y) dimension */
				float* x, /* x coordinates */
				float* y, /* y coordinates */
				float* coef /* Spline coefficients */)
/*< Function to calculate natural cubic spline coefficients

Note: It Receives n points and two vectors x and y with n dimension.
It returns a coefficients vector with 4 coefficients for each of the
n-1 natural cubic splines, coef[(n-1)*4].

IMPORTANT: The number of points must be equal or major than 3 (n>3)
and x vector must be in crescent order.

>*/
{

	float s2[n]; // Second derivatives matrix
	int i, ip1, ip2, im1, m; // Loop counter
	float hb, ha, deltaa, deltab, t; // temporary variables
	float e[n-2]; // hi's vector
	float dp[n-2]; // main diagonal

	/* Vectors dimension must be major than 3 */
	if(n<3) sf_error("Vectors dimension n must be major than 3\n");

	/* x vector must be in crescent order */
	for(i=1;i<n;i++){
		if(x[i-1]>x[i]) sf_error("Vector x should be in ascending order\n");
	}

	/* Simetric tridiagonal linear system build */
	ha = x[1]-x[0]; deltaa = (y[1]-y[0])/ha; m=n-2;
	for(i=0;i<m;i++){
		ip1 = i+1; ip2 = i+2;
		hb = x[ip2]-x[ip1];
		deltab = (y[ip2]-y[ip1])/hb;
		e[i] = hb; dp[i] = 2*(ha+hb);
		s2[ip1] = 6*(deltab-deltaa);
		ha=hb; deltaa=deltab;
	}

	/* Gauss elimination */
	for(i=1;i<m;i++){
		ip1=i+1; im1=i-1;
		t = e[im1]/dp[im1];
		dp[i] = dp[i]-t*e[im1];
		s2[ip1] = s2[ip1]-t*s2[i];
	}

	/* Retroactive substitutive solution */
	s2[m]=s2[m]/dp[m-1];
	for(i=m-1;i>0;i--){
		ip1=i+1; im1=i-1;
		s2[i]=(s2[i]-e[im1]*s2[ip1])/dp[im1];
	}
	s2[0]=0; s2[n-1]=0;

	/* Calculate spline coefficients */
	for(i=0;i<n-1;i++){
		ha = x[i+1]-x[i];
		coef[0+i*4] = (s2[i+1]-s2[i])/(6*ha);
		coef[1+i*4] = s2[i]/2;
		coef[2+i*4] = (y[i+1]-y[i])/ha-(s2[i+1]+2*s2[i])*(ha/6);
		coef[3+i*4] = y[i];
	}
}

void calcInterfacesZcoord(	float *zi, /* Interfaces depth coordinates */
				int nint, /* Number of interfaces */
				float xs, /* x coordinate */
				int si, /* Spline index */
				float **coef /* Cubic spline coefficients */)
/*< Calculate depth coordinates of the interfaces
 * Note: This function calculates interfaces depth coordinates and stores it
 * in the zi vector.
  >*/
{
	int i; // Loop counter

	for(i=0;i<nint;i++)
		zi[i] = coef[i][si*4+0]*xs*xs*xs+coef[i][si*4+1]*xs*xs+coef[i][si*4+2]*xs+coef[i][si*4+3];
}

itf2d itf2d_init(float *sz, /* Interface nodepoints z(x) */
		 int n1, /* Number of nodes */
		 float o1, /* Axis origin */
		 float d1 /* nodes sampling */)
/*< Initialize interface struct >*/
{
	itf2d itf;
	int i;
	float *x;

	itf = (itf2d) sf_alloc(1,sizeof(struct Interface2d));

	itf->n = n1;
	itf->o = o1;
	itf->d = d1;

	x = sf_floatalloc(n1);
	itf->z = sf_floatalloc(n1);

	for(i=0;i<n1;i++){
		x[i] = i*d1+o1;
		itf->z[i] = sz[i];
	}

	/* Calculate coefficients matrix (interfaces interpolation) */
	itf->coef = sf_floatalloc(4*(n1-1));
	calculateSplineCoeficients(n1,x,sz,itf->coef);

	return itf;
}

float getZCoordinateOfInterface(
				itf2d itf, /* Interface */
				float x /* x coordinate */)
/*< Get z coordinate of the interface given x coordinate >*/
{
	float z;
	int is;
	float xs;

	is = (x-itf->o)/itf->d;

	xs = x - ((is*itf->d)+itf->o);

	z = itf->coef[is*4+0]*xs*xs*xs+itf->coef[is*4+1]*xs*xs+itf->coef[is*4+2]*xs+itf->coef[is*4+3];

	return z;
}

int itf2d_n(itf2d itf)
/*< Get number of interface nodepoints >*/
{return itf->n;}

float itf2d_o(itf2d itf)
/*< Get interface axis origin >*/
{return itf->o;}

float itf2d_d(itf2d itf)
/*< Get interface nodepoints sampling >*/
{return itf->d;}

void itf2d_seto(itf2d itf,float o)
/*< Set interface axis origin >*/
{itf->o=o;}

void itf2d_setZNodepoints(
		itf2d itf, /* Interface */
		float *z /* Nodepoints z(x) */)
/*< Update interface nodepoints z(x) >*/
{
	int i;
	float *x;

	x = sf_floatalloc(itf->n);
	for(i=0;i<itf->n;i++){
		x[i] = itf->o+(i*itf->d);
		itf->z[i]=z[i];
	}
	calculateSplineCoeficients(itf->n,x,z,itf->coef);
}

void itf2d_getZNodepoints(
		itf2d itf, /* Interface */
		float *z /* Nodepoints z(x) */)
/*< Get interface nodepoints z(x) >*/
{
	int i;
	for(i=0;i<itf2d_n(itf);i++)
		z[i]=itf->z[i];
}

void itf2d_getSplineCoefficients(
		itf2d itf, /* Interface */
		float *c, /* 4 Spline coefficients */
		int is /* Spline index */)
/*< Get Spline Coefficients from coefficients vector for a given spline index
Note: Coefficients vector has 4 coefficients for each (nx-1) spline
>*/
{
	c[0] = itf->coef[is*4+0];
	c[1] = itf->coef[is*4+1];
	c[2] = itf->coef[is*4+2];
	c[3] = itf->coef[is*4+3];
}
