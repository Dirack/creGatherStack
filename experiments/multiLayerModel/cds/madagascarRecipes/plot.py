#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# plot.py  (Madagascar Recipe)
#
# Purpose: Recipe to generate plot files (VPL).
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
Madagascar recipe to plot

Define functions to generate vpl files.
'''

if __name__ == "__main__":
	print(__doc__)
	exit()

# Madagascar package
from rsf.proj import *

__author__="Rodolfo Dirack <rodolfo_profissional@hotmail.com>"
__version__="1.0"

def velplot(title,label1='Depth',unit1='Km'):
	'''
	Velocity ploting function
	:param title: RSF filename, velocity file
	:param label1: string, first axis label
	:param unit1: string, first axis unit
	'''
	
	return '''
	grey color=j allpos=y title="%s" scalebar=y
	barlabel=Velocity barunit=Km/s
	label1="%s" unit1="%s" label2=Lateral unit2=Km
	barreverse=y pclip=100 bias=2.8 
	''' % (title,label1,unit1)


