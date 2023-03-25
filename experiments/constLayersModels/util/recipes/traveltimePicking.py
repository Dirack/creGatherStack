#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# SConstruct (Python3)
# 
# Purpose: Traveltime picking and parameters search.
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

def pick(parametersCube,nitf):

    # CRS parameters smoothing
    Flow(["parametersCube2","mask"],[parametersCube],
            '''
            parsmoother rect1=5 rect2=5 smin=0.1 f=1 dbeta=0.5 mask=${TARGETS[1]}
            ''')

    Flow('maskedParameters',['parametersCube2','mask'],'math m=${SOURCES[1]} output="input*m"')

    # Use smoothed parameters
    parametersCube='parametersCube2'

    picks=[]
    for i in range(nitf):
            Flow('pick'+str(i)+'.txt',parametersCube,'window n3=1 f3=3 | ipick color=j title="Pick-interface-%d"' %i) 
            picks.append('pick'+str(i)+'.txt')
            files=['t0s'+str(i),'m0s'+str(i)]
            k=0
            for f in files:
                    Flow(f+'.asc','pick'+str(i)+'.txt',
                    '''
                    pick2asc ${TARGETS} %d
                    ''' % k)

                    Flow(f,f+'.asc','dd type=float form=native | put n2=1 d2=1 o2=0')
                    k=k+1

            files=['rns'+str(i),'rnips'+str(i),'betas'+str(i)]
            k=0
            for f in files:
                    Flow(f,[parametersCube,'t0s'+str(i),'m0s'+str(i)],
                    '''
                    window n3=1 f3=%d |
                    getparameter t0s=${SOURCES[1]} m0s=${SOURCES[2]}
                    ''' %k) 
                    k=k+1
