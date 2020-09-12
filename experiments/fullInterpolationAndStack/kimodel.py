#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# kimodel.py  (Madagascar Recipe)
#
# Purpose: Recipe to Kirchhoff modeling of a gaussian reflector.
# 
# Important!: It should be called from a SConstruct 
#
# Site: https://dirack.github.io
# 
# Version 2.0
#
# Programer: Rodolfo A. C. Neves (Dirack) 04/03/2020
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Madagascar package
from rsf.proj import *

def kirchoffModeling(filename='dataCube'):
    '''
    Modeling function of a gaussian reflector
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

    # Kirchoff Modeling
    Flow(filename,'gaussianReflector reflectorDip',
         '''
         kirmod cmp=y dip=${SOURCES[1]} 
         nh=161 dh=0.025 h0=0
         ns=401 ds=0.025 s0=0
         freq=10 dt=0.004 nt=1001
         vel=1.5 gradz=0.5 gradx=0.0 verb=y |
         put d2=0.0125 label3="CMP" unit3="Km" label2="Offset" unit2="Km" label1=Time unit1=s
         ''')


