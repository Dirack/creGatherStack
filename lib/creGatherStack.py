#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# creGatherStack  (Madagascar Recipe)
#
# Purpose: Common Reflection Element (CRE) stack
#
# IMPORTANT: This is a modified version adapted for VFSA 2.0 package
# that is incompatible with the previous VFSA package versions.
#
# Site: https://dirack.github.io
# 
# Version 2.0
#
# Programer: Rodolfo A. C. Neves (Dirack) 08/02/2021
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Madagascar package
from rsf.proj import *

def creGatherStack(
	creStackedSection,
	parametersCube,
	dataCube,
	interpolatedDataCube,
	repeat,
	aperture,
	cds,
	nm0,
	om0,
	dm0,
	nt0,
	ot0,
	dt0,
	v0
	):
	'''

	CRE Gather Stacking function

	=> It needs a datacube (data organized in time x Offset x CMP cordinates); and a
	interpolatedDataCube, that is the datacube interpolated with the pefInterpolation
	function in pefInterpolation.py Madagascar recipe.

	=> The number of offsets in interpolatedDataCube should be major or equal to the
	number of offsets to stack defined in the aperture parameter.

	=> CDS condition is to use (RN=RNIP) and non-hyperbolic CRS traveltime approximation
	as CRE stacking curve instead of CRE traveltime approximation (Default). This option is
	controled with cds boolean parameter (True, use CDS condition; False, no use).

	:output creStackedSection: RSF filename, CRE stacked section
	:output parametersCube: RSF filename, Parameters cube for each (t0,m0) pair
	:input dataCube: RSF filename, datacube (time x Offset x CMP)
	:input interpolatedDataCube: RSF filename, datacube interpolated with pefInterpolation.py recipe
	:param repeat: int, number of times to do VFSA optimization
	:param aperture: int, number of traces to stack ( < or = to number of offsets in interpolatedDataCube)
	:param cds: bool, if True use cds condition in CRE stacking
	:param nm0: int, Number of CMP samples in CRE stacked section
	:param om0: float, CMP axis origin in CRE stacked section
	:param dm0: float, CMP sampling in CRE stacked section
	:param nt0: int, Number of Time samples in CRE stacked section
	:param ot0: float, Time axis origin in CRE stacked section
	:param dt0: float, Time sampling in CRE stacked section
	:param v0: float, near surface velocity
	'''

	if type(nm0) is not int:
		raise TypeError("number of CMP samples nm0 should be int")
		return False
		
	if type(nt0) is not int:
		raise TypeError("number of Time samples nt0 should be int")
		return False

	if type(cds) is not bool:
		raise TypeError("cds parameter should be bool")
		return False
	
	if dataCube == interpolatedDataCube:
		raise ValueError("dataCube and interpolatedDataCube filenames should not be equal")
		return False

	Flow(parametersCube,dataCube,
	'''
	vfsacrsnh nm0=%d om0=%g dm0=%g nt0=%d ot0=%g dt0=%g v0=%g repeat=%d
	'''%(nm0,om0,dm0,nt0,ot0,dt0,v0,repeat))

	creTrajectories = 'creTrajectories-'+dataCube

	Flow(creTrajectories,[dataCube,parametersCube],
		'''
		cretrajec param=${SOURCES[1]} nm0=%d om0=%g dm0=%g nt0=%d ot0=%g dt0=%g verb=y 
		'''%(nm0,om0,dm0,nt0,ot0,dt0))

	creGathers = 'creGathers-'+dataCube
	mhCoordinates = 'mhCoordinates-'+dataCube

	Flow([creGathers,mhCoordinates],[dataCube,creTrajectories],
		'''
		getcregather cremh=${SOURCES[1]} m=${TARGETS[1]} nm0=%g nt0=%g aperture=%d |
		put label1=Time unit1=s label2=Offset unit2=Km label3=t0 unit3=s
		label4=m0 unit4=Km n3=%d d3=%g o3=%g n4=%d d4=%g o4=%g
		''' % (nm0,nt0,aperture,nt0,dt0,ot0,nm0,dm0,om0))

	creTimeCurves = 'creTimeCurves-'+dataCube

	Flow(creTimeCurves,[mhCoordinates,parametersCube],
		'''
		getcretimecurve param=${SOURCES[1]} nm0=%d om0=%g dm0=%g nt0=%d ot0=%g dt0=%g verb=y v0=%g |
		put label1=Offset unit1=Km label2=t0 unit2=s label3=m0 unit3=Km
		n2=%d d2=%g o2=%g n3=%d d3=%g o3=%g
		'''%(nm0,om0,dm0,nt0,ot0,dt0,v0,nt0,dt0,ot0,nm0,dm0,om0))

	Flow(creStackedSection,[creGathers,creTimeCurves],
		'''
		crestack aperture=%d verb=y timeCurves=${SOURCES[1]} |
		put label1=t0 unit1=s label2=m0 unit2=Km
		''' %(aperture))

	return True
