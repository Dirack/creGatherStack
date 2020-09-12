#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# kimodel.py  (Madagascar Recipe)
#
# Purpose: Recipe to Kirchhoff modeling.
# 
# Important!: It should be called from a SConstruct 
#
# Site: http://www.dirackslounge.online
# 
# Version 1.0
#
# Programer: Rodolfo A. C. Neves (Dirack) 04/03/2020
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Selfdoc string
'''
Madagascar recipe to Kirchhoff modeling

Define functions to generate subsurface models, apply Kirchhoff modeling
and Kirchhoff Newton modeling.
'''

if __name__ == "__main__":
	print(__doc__)
	exit()

# Madagascar package
from rsf.proj import *

__author__="Rodolfo Dirack <rodolfo_profissional@hotmail.com>"
__version__="1.0"

def arr2str(array,sep=' '):
	'''
	Convert a tuple into a comma separeted string
	'''
	return string.join(map(str,array),sep)


def multiLayerModel(
	interfaces,
	dipsfile,
	modelfile,
	xmax,
	zmax,
	layers,
	velocities
	):
	'''

	Generate a multi layer model to use in the program sfkirmod_newton

	:out interfaces: RSF filename, interpolated interfaces file
	:out dipsfile: RSF filename, dips of interfaces
	:out modelfile: RSF filename, model for ploting
	:param xmax: interger, max x axis model distance
	:param zmax: interger, max z axis model depth
	:param layers: tuple array, points describing interfaces
	:param velocities: tuple, layers velocities in Km/s
	'''
	vstr=arr2str(velocities,',')
	
	n1 = len(layers[0])
	n2 = len(layers)

	Flow('layers.asc',None,
	     '''
	     echo %s
	     n1=%d n2=%d o1=0 d1=%g
	     data_format=ascii_float in=$TARGET
	     ''' % (string.join(map(arr2str,layers),' '),
		    n1,n2,xmax/(n1-1)))
	Flow('layers','layers.asc','dd form=native')

	d = 0.0101 # non-round for reproducibility

	Flow(interfaces,'layers',
	     'spline o1=0 d1=%g n1=%d' % (d,int(1.5+xmax/d)))
	Flow(dipsfile,interfaces,'deriv scale=y')

	Flow(modelfile,interfaces,
	     '''
	     unif2 d1=%g n1=%d v00=%s
	     ''' % (d,int(1.5+zmax/d),vstr))

def kirchoffNewtonModeling(
	reflectors, 
	reflectorsDip,
	filename,
	velocities):
	'''
	Kirchhoff modeling for a multi layer model
	'''	
	vstr=arr2str(velocities,',')

	# Kirchoff modeling for multi layer model
	Flow(filename,[reflectors,reflectorsDip],
		'''
		kirmod_newton nt=1001 dt=0.004 freq=10
		ns=201 ds=0.025 nh=161 dh=0.025 h0=0 s0=0 verb=y cmp=y
		vstatus=0 velocity=%s debug=n fwdxini=y
		xref=0 zref=0 dip=${SOURCES[1]} |
		put d2=0.0125 label3="CMP" unit3="Km" label2="Offset" unit2="Km" label1=Time unit1=s
		''' % (vstr))

def gaussianReflector(filename='gaussianReflector'):
    '''

    Generate a gaussian reflector to use in the program sfkirmod

    :param filename: RSF filename, gaussian reflector file 
    '''

    # Modeling: Gaussian reflector in a velocity linear model
    # velocity increases with depth with a 0.5 velocity gradient
    Flow('gaussianReflector',None,
         '''
         math d1=0.01 n1=2001 o1=-5 unit1=km label1=Offset
         output="4-3*exp(-(x1-5)^2/9)"
         ''')

    # Velocity Model
    Flow('velocityModel','gaussianReflector',
         '''
         window min1=0 max1=10 |
         spray axis=1 n=451 d=0.01 o=0 label=Depth unit=km |
         math output="1.5+0.5*x1+0.0*x2"
         ''')

    Flow('reflectorDip','gaussianReflector','math output="2/3*(x1-5)*input" ')


def kirchoffModeling(
	filename,
	reflector,
	reflectorDip,
	nh,
	dh,
	h0,
	ns,
	ds,
	s0,
	freq,
	dt,
	nt,
	v0,
	gradz
	):
	'''

	Kirchhoff modeling function. Generate (time,cmp,offset) datacube for
	a given v(z) model (Velocity increases with depth).

	:out filename: RSF filename, Modeled data cube
	:param reflector: RSF filename, interfaces file
	:param reflectorDip: RSF filename, interfaces dips file
	:param nh: integer, number of offsets
	:param dh: float, offset sampling
	:param h0: float, first offset
	:param ns: integer, number of shots/cmps
	:param ds: float, shots/cmps sampling
	:param s0: float, first shot/cmp position
	:param freq: integer, ricker pulse frequency
	:param dt: float, time sampling
	:param nt: float, number of time samples
	:param v0: float, near surface velocity
	:param gradz: float, velocity gradient
	'''

	halfOffset = dh/2.

	# Kirchoff Modeling
	Flow(filename,[reflector, reflectorDip],
         '''
         kirmod cmp=y dip=${SOURCES[1]} 
         nh=%i dh=%g h0=%g
         ns=%i ds=%g s0=%g
         freq=%i dt=%g nt=%i
         vel=%g gradz=%g gradx=0.0 verb=y |
         put d2=%g label3="CMP" unit3="Km" label2="Offset" unit2="Km" label1=Time unit1=s
         ''' % (nh,dh,h0,ns,ds,s0,freq,dt,nt,v0,gradz,halfOffset))
	 
