#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# SConstruct (Python3)
# 
# Purpose: CRE stacking for a constant velocity layers model.
# 
# Site: https://www.geofisicando.com
# 
# Version 1.0
# 
# Programmer: Rodolfo A C Neves (Dirack) 31/01/2022
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Madagascar Package
from rsf.proj import *

__author__="Rodolfo Dirack <rodolfo_profissional@hotmail.com>"
__version__="1.0"
__site__="https://www.geofisicando.com"

Help('''
    CRE stacking for a constant velocity layers model
    =================================================

    Author: %s
    Version: %s
    Site: %s
    ''' % (__author__,__version__,__site__))


# Madagascar Recipes
from rsf.recipes.creGatherStack import modeling
from rsf.recipes.creGatherStack import interpolation
from rsf.recipes.creGatherStack import vfsa
from rsf.recipes.creGatherStack import stack
from rsf.recipes.utils import arr2str
from rsf.recipes.utils import velplot
from rsf.recipes.utils import plotStackedSection

def creGatherStack(modelname,xmax,zmax,layers,velocities):

    # Main Files
    trueModel='trueModel'
    stackedSection='stackedSection'
    parametersCube='parametersCube'
    dataCube='multiLayerDataCube'
    interpolatedDataCube='interpolatedDataCube2'

    # Establish building dependencies
    Depends('interpolatedDataCube.rsf','multiLayerDataCube.rsf')
    Depends('interpolatedDataCube2.rsf','interpolatedDataCube.rsf')
    Depends('crsParameters-m0-0-t0-0.rsf','interpolatedDataCube2.rsf')

    Help('''
    ### Kirchhoff Modeling ###

    Generate the multi layers velocity model and plot
    Use Kirchhoff modeling to build seismic data from this model
    ''')

    # Generate velocity model and seismic data cube
    nt=1001
    dt=0.004
    nm=241
    dm=0.025
    nh=161
    dh=0.025

    modeling(trueModel,
            dataCube,
            xmax,
            zmax,
            layers,
            velocities,
            nt,
            dt,
            nm,
            dm,
            nh,
            dh)

    Flow('noisyDataCube',dataCube,'noise seed=2011 range=0.051')
    dataCube='noisyDataCube'

    Result(trueModel,velplot(modelname))

    Help('''
    ### PEF interpolation ###

    PEF interpolation to increase CMP sampling for CRE stacking
    You can use default values for PEF coefficients and PEF Smooth radius
    or pass it through command line

    PEF interpolation is done twice
    ''')

    # PEF interpolation coefficients and smooth radius
    a1=int(ARGUMENTS.get('a1',10))
    a2=int(ARGUMENTS.get('a2',2))
    rect1=int(ARGUMENTS.get('rect1',50))
    rect2=int(ARGUMENTS.get('rect2',2))

    # Number of offsets to interpolate
    nhi=int(ARGUMENTS.get('nhi',nh))

    interpolation(dataCube,
            'interpolatedDataCube',
            interpolatedDataCube,
            nm,
            dm,
            nt,
            dt,
            nhi,
            a1,
            a2,
            rect1,
            rect2)

    Help('''
    ### Very Fast Simulated Annealing (VFSA) ####

    Use Very Fast Simulated Annealing global optimization to get zero offset CRS parameters
    (RN, RNIP and BETA) from interpolated data cube. These parameters are used to obtain CRE
    gathers and CRE traveltime curves to CRE stacking
    ''')


    # VFSA Parameters
    v0 = float(ARGUMENTS.get('v0',1.5))
    ot0 = float(ARGUMENTS.get('ot0',1.0))
    dt0 = float(ARGUMENTS.get('dt0',0.008))
    nt0 = int(ARGUMENTS.get('nt0',251))
    om0 = float(ARGUMENTS.get('om0',1.5))
    dm0 = float(ARGUMENTS.get('dm0',0.025))
    nm0 = int(ARGUMENTS.get('nm0',121))
    aperture = int(ARGUMENTS.get('aperture',25))
    repeat = int(ARGUMENTS.get('repeat',4))
    itmax = int(ARGUMENTS.get('itmax',500))
    cds = bool(ARGUMENTS.get('cds',False))

    # VFSA global optimization CRS parameters
    vfsa(parametersCube,
            interpolatedDataCube,
            nm0,
            om0,
            dm0,
            nt0,
            ot0,
            dt0,
            v0,
            repeat,
            itmax,
            rnmin=2,
            rnmax=10,
            rnipmin=0.3,
            rnipmax=3.0,
            betamin=-1.0,
            betamax=1.0,
            half='n',
            verb='y')

    # CRS parameters smoothing
    Flow(['parametersCube2','mask'],parametersCube,
            '''
            parsmoother mask=${TARGETS[1]} rect1=10 rect2=10 smin=0.3 f=0.5 dbeta=0.5
            ''')

    Help('''
    ### CRE Stacking ###

    Generate CRE trajectories, traveltime curves and stack
    ''')

    # Use smoothed parameters
    parametersCube='parametersCube2'

    stack(stackedSection,
            interpolatedDataCube,
            parametersCube,
            nm0,
            om0,
            dm0,
            nt0,
            ot0,
            dt0,
            v0,
            aperture)

    Result(stackedSection,plotStackedSection("Stacked Section"))
