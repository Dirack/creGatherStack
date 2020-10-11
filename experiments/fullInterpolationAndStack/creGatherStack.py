#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# creGatherStack  (Madagascar Recipe)
#
# Purpose: Common Reflection Element (CRE) stack
#
# Site: https://dirack.github.io
# 
# Version 2.0
#
# Programer: Rodolfo A. C. Neves (Dirack) 11/10/2020
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Madagascar package
from rsf.proj import *

def creGatherStack(
	creStackedSection,
	parametersCubeFile,
	dataCube,
	interpolatedDataCube,
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
	:output parametersCubeFile: RSF filename, Parameters cube for each (t0,m0) pair
	:input dataCube: RSF filename, datacube (time x Offset x CMP)
	:input interpolatedDataCube: RSF filename, datacube interpolated with pefInterpolation.py recipe
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

	files = []
	parametersCubeForM0List = []
	for i in range(nm0):

		parametersCube = []
		creGatherCube = []
		creTimeCurveCube = []
		creGatherCubeForM0List = []
		creTimeCurveCubeForM0List = []
		creGatherIndex = 0

		m0 = om0 + (i * dm0)

		for j in range(nt0):

			t0 = ot0 + (dt0 * j)

			crsParameters = 'crsParameters-m0-%g-t0-%g' % (i,j)
			creMhCoordinates = 'creMhCoordinates-m0-%g-t0-%g' % (i,j)
			creGather = 'creGather-m0-%g-t0-%g' % (i,j)
			creMcoordinate = 'creMcoordinate-m0-%g-t0-%g' % (i,j)
			creTimeCurve = 'creTimeCurve-m0-%g-t0-%g' % (i,j)
			creGatherPlot = 'crePlot-m0-%g-t0-%g' % (i,j)

			# Very Fast Simulated Aneelling Global Optimization (VFSA)
			Flow(crsParameters,dataCube,
				'''
				vfsacrsnh m0=%g v0=%g t0=%g verb=y repeat=3
				''' % (m0,v0,t0))

			# Calculate CRE trajectory
			Flow(creMhCoordinates,[interpolatedDataCube,crsParameters],
				'''
				cretrajec verb=y m0=%g param=${SOURCES[1]} |
				put unit1="Offset" label1="Km"
				''' % (m0))

			#Get CRE Gather from interpolated Data Cube
			Flow([creGather,creMcoordinate],[interpolatedDataCube,creMhCoordinates],
				'''
				getcregather verb=y cremh=${SOURCES[1]} m=${TARGETS[1]} aperture=%i |
	      put label1="Time" unit1="s" label2="Offset" unit2="km" 
				''' %(aperture))

			# Calculate CRE traveltime curve t(m,h)
			Flow(creTimeCurve,[creMcoordinate, crsParameters],
				'''
				getcretimecurve param=${SOURCES[1]} cds=%s t0=%g m0=%g v0=%g verb=y |
	      put label1="Offset" unit1="Km" 
				''' % (("y" if cds else "n"),t0,m0,v0))

			parametersCube.append(crsParameters)
			creGatherCube.append(creGather)
			creTimeCurveCube.append(creTimeCurve)
			creGatherIndex = creGatherIndex + 1
		
		# Concatenate crs Parameters for each m0
		parametersCubeForM0 = "crsParameters-m0-%i" % i
		parametersCubeForM0List.append(parametersCubeForM0)
		Flow(parametersCubeForM0,parametersCube,
			'''
			rcat axis=2 ${SOURCES[1:%d]}
			''' % nt0)

		# Concatenate cre gathers for each m0
		creGatherCubeForM0 = "creGatherCube-m0-%i" % i
		creGatherCubeForM0List.append(creGatherCubeForM0)
		Flow(creGatherCubeForM0,creGatherCube,
			'''
			rcat axis=3 ${SOURCES[1:%d]}
			''' % nt0)

		# Concatenate cre Time curves for each m0
		creTimeCurveCubeForM0 = "creTimeCurveCube-m0-%i" % i
		creTimeCurveCubeForM0List.append(creTimeCurveCubeForM0)
		Flow(creTimeCurveCubeForM0,creTimeCurveCube,
			'''
			rcat axis=2 ${SOURCES[1:%d]}
			'''% nt0)

		# Stack one m0 per turn
		creTimeCurveCube = []
		creGatherCube = []
		parametersCube = []
		creGatherTrace = "creGatherTrace-m0-%i" % i
		creTimeCurveTrace = "creTimeCurveTrace-m0-%i" % i
		creStackedTrace = "creStackedTrace-m0-%i" % i

		# Get cre Gathers organized by t0 and m0
		Flow(creGatherTrace,creGatherCubeForM0List,
			'''
			put n4=1 d4=%g o4=%g d3=%g o3=%g label3=t0 unit3=s label4=m0 unit4=Km
			''' % (dm0,m0,dt0,ot0))

		# Get all the traveltime curves organized by t0 and m0
		Flow(creTimeCurveTrace,creTimeCurveCubeForM0List,
			'''
			put label3="m0" unit3="Km" label2="t0" unit2="s" d2=%g o2=%g d3=%g o3=%g
			''' % (dt0,ot0,dm0,m0))

		# CRE stacking
		Flow(creStackedTrace,[creGatherTrace,creTimeCurveTrace],
			'''
			crestack timeCurves=${SOURCES[1]} verb=y aperture=%i |
			put label1=t0 unit1=s label2=m0 unit2=Km --out=stdout
			''' %(aperture))

		files.append(creStackedTrace)

	# Stacked section depends of the last CRE stacked trace
	Depends(creStackedSection+'.rsf',[dataCube,
				      'creStackedTrace-m0-'+str(nm0-1)+'.rsf',
				      'creGatherTrace-m0-'+str(nm0-1)+'.rsf'])

	# Build the cre stacked section
	# throughout cre stacked traces sorting
	length = len(files)
	sortedFiles = []
	for i in range(length):
		string = 'creStackedTrace-m0-%i.rsf' % i
		sortedFiles.append(string)  

	Flow(creStackedSection,sortedFiles,
		'''
		rcat axis=2 ${SOURCES[1:%d]} --out=stdout
		''' % len(files))

	#Build the parameters cube
	Flow(parametersCubeFile,parametersCubeForM0List,
		'''
		rcat axis=3 ${SOURCES[1:%d]} --out=stdout |
		put label2=t0 unit2=s label3=m0 unit3=Km d2=%g o2=%g d3=%g o3=%g
		''' % (len(parametersCubeForM0List),dt0,ot0,dm0,om0))

	return True
