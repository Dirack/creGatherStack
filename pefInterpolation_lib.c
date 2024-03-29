/*
	 pefInterpolation.c (c)
	 
	 Purpose: Model interface 2D interpolated with cubic splines.
	 	 
	 Version 1.0
	 
	 Site: https://dirack.github.io
	 
	 Programmer: Rodolfo A. C. Neves (Dirack) 25/12/2021

	 Email:  rodolfo_profissional@hotmail.com

	 License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

*/
#include <rsf.h>
#include "mask4apef.h"
#include "pefInterpolation_lib.h"
#include "nmis.h"

void apef(float** trace, int nt)
/*<TODO>*/
{
	int n[SF_MAX_DIM];
	int m[SF_MAX_DIM];
	int rect[SF_MAX_DIM];
	int a[SF_MAX_DIM];
	int ndim, mdim=2, nd, ns, n12, i, j, niter;
	int i1, i2, i3, j1, j2, j3, jump=2, i4, n4;
	float *d, *f, *g, mean, *ff;
	bool *mask;
	int n1, n2, nf1, nf2, nf3, nf4, n3, nf;
	float *mm;
	bool *known;

	ndim=mdim;
	niter=50;

	n4 = 1;

	a[0] = 10;
	a[1] = 3;
	a[2] = 1;
	n[2] = 1;
	m[0] = nt;
	m[1] = 3;
	m[2] = 1;

	for (j=0; j < ndim; j++) {
		n[j] = m[j];
	}
	n[ndim] =1;
	for (j=0; j < ndim; j++) {
		n[ndim] *= a[j];
	}

	nd = 1;
	for (j=0; j < ndim; j++) {
		nd *= m[j];
	}
	rect[0]=25;
	rect[1]=3;

	ns = n[ndim];
	n12 = nd*ns;

	mask = sf_boolalloc(nd);

	d = sf_floatalloc(n12);
	f = sf_floatalloc(n12);
	ff = sf_floatalloc(n12);
	g = sf_floatalloc(nd);

	sf_multidivn_init(ns, ndim, nd, m, rect, d, NULL, false); 

	for(i=0;i<m[0];i++) g[i]=1;
	for(i=0;i<m[0];i++) g[i+m[0]]=0;
	for(i=0;i<m[0];i++) g[i+2*m[0]]=1;

	mask4apef (a, jump, m, g, mask);

	for(i=0;i<m[0];i++) g[i]=trace[0][i];
	for(i=0;i<m[0];i++) g[i+m[0]]=trace[1][i];
	for(i=0;i<m[0];i++) g[i+2*m[0]]=trace[2][i];

	for (i3=0; i3 < a[2]; i3++) {
	    for (i2=0; i2 < a[1]; i2++) {
		for (i1=-a[0]/2; i1 < (a[0]+1)/2; i1++) {
		    for (j3=0; j3 < m[2]; j3++) {
			for (j2=0; j2 < m[1]; j2++) {
			    for (j1=0; j1 < m[0]; j1++) {
				if (0==i2 && 0==i3 && 0 >=i1) {
				    d[i3*a[1]*a[0]*m[2]*m[1]*m[0]+
				      i2*a[0]*m[2]*m[1]*m[0]+
				      (i1+a[0]/2)*m[2]*m[1]*m[0]+
				      j3*m[1]*m[0]+j2*m[0]+j1] = 0.;
				} else {
				    if ((j1+i1*jump)<0 || (j1+i1*jump)>=m[0] ||
					(j2+i2*jump)<0 || (j2+i2*jump)>=m[1] ||
					(j3+i3*jump)<0 || (j3+i3*jump)>=m[2]) {
					d[i3*a[1]*a[0]*m[2]*m[1]*m[0]+
					  i2*a[0]*m[2]*m[1]*m[0]+
					  (i1+a[0]/2)*m[2]*m[1]*m[0]+
					  j3*m[1]*m[0]+j2*m[0]+j1] = 0.;
				    } else {
					d[i3*a[1]*a[0]*m[2]*m[1]*m[0]+
					  i2*a[0]*m[2]*m[1]*m[0]+
					  (i1+a[0]/2)*m[2]*m[1]*m[0]+
					  j3*m[1]*m[0]+j2*m[0]+j1] = 
					    g[(j3+i3*jump)*m[1]*m[0]+
					      (j2+i2*jump)*m[0]+
					      (j1+i1*jump)];
				    }
				}
			    }
			}
		    }
		}
	    }
	}
	
	mean = 0.;
	for(i=0; i < n12; i++) {
	    mean += d[i]*d[i];
	}
		
	mean = sqrtf (mean/n12);
	
	for(i=0; i < n12; i++) {
	    d[i] /= mean;
	}
	for(i=0; i < nd; i++) {
	    g[i] /= mean;
	}

	    for (j3=0; j3 < m[2]; j3++) {
		for (j2=0; j2 < m[1]; j2++) {
		    for (j1=0; j1 < m[0]; j1++) {
			if (!mask[j3*m[1]*m[0]+j2*m[0]+j1]) {
			    for (i3=0; i3 < a[2]; i3++) {
				for (i2=0; i2 < a[1]; i2++) {
				    for (i1=0; i1 < a[0]; i1++) {
					d[i3*a[1]*a[0]*m[2]*m[1]*m[0]+
					  i2*a[0]*m[2]*m[1]*m[0]+
					  i1*m[2]*m[1]*m[0]+
					  j3*m[1]*m[0]+j2*m[0]+j1] = 0.;
				    }
				}
			    }
			    g[j3*m[1]*m[0]+j2*m[0]+j1] = 0.;
			}
		    }
		}
	    } 
	
	sf_multidivn (g,f,niter);
	
	for (i3=0; i3 < a[2]; i3++) {
	    for (i2=0; i2 < a[1]; i2++) {
		for (i1=0; i1 < a[0]; i1++) {
		    for (j3=0; j3 < m[2]; j3++) {
			for (j2=0; j2 < m[1]; j2++) {
			    for (j1=0; j1 < m[0]; j1++) {
				if (0==i2 && 0==i3 && a[0]/2==i1) {
				    ff[j3*m[1]*m[0]*a[2]*a[1]*a[0]+
				       j2*m[0]*a[2]*a[1]*a[0]+
				       j1*a[2]*a[1]*a[0]+
				       i3*a[1]*a[0]+
				       i2*a[0]+
				       i1] = 1.0;
				} else if (0==i2 && 0==i3 && a[0]/2>i1) {
				    ff[j3*m[1]*m[0]*a[2]*a[1]*a[0]+
				       j2*m[0]*a[2]*a[1]*a[0]+
				       j1*a[2]*a[1]*a[0]+
				       i3*a[1]*a[0]+
				       i2*a[0]+
				       i1] = 0.0;
				} else {
				    ff[j3*m[1]*m[0]*a[2]*a[1]*a[0]+
				       j2*m[0]*a[2]*a[1]*a[0]+
				       j1*a[2]*a[1]*a[0]+
				       i3*a[1]*a[0]+
				       i2*a[0]+
				       i1] = -1.*
					f[i3*a[1]*a[0]*m[2]*m[1]*m[0]+
					  i2*a[0]*m[2]*m[1]*m[0]+
					  i1*m[2]*m[1]*m[0]+
					  j3*m[1]*m[0]+
					  j2*m[0]+
					  j1];
				}
			    }
			}
		    }
		}
	    }
	}


	niter=25;

	n1=nt;
	n2=m[1];
	n3=1;

	nf1=a[0];
	nf2=a[1];
	nf3=nt;
	nf4=m[1];

	nf = nf1*nf2*nf3*nf4;
	mm = sf_floatalloc(n1*n2);
	known = sf_boolalloc(n1*n2);

	for (i=0; i < n1; i++) {
		known[i]=true;
		known[i+n1]=false;
		known[i+2*n1]=true;
	}

	for(j=0;j<n2;j++){
		for (i=0; i < n1; i++) {
			mm[i]=trace[j][i];
		}
	}
	
	nmis (niter, nf1, nf2, nf3, nf4, ff, mm, known, 0., false);
	
	for(j=0;j<n2;j++){
		for (i=0; i < n1; i++) {
			trace[j][i]=mm[i];
		}
	}
	
	sf_multidivn_close();
	free(mask);
	free(mm);
	free(known);
	free(g);
	free(ff);
	free(f);
	free(d);
}
