#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# errorReport.py  (Madagascar Recipe)
#
# Purpose: SCons error report function.
# 
# Important!: It should be called from a SConstruct 
#
# Site: http://www.dirackslounge.online
# 
# Version 1.0
#
# Programer: Rodolfo A. C. Neves (Dirack) 01/06/2020
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Selfdoc string
'''
Python function to report errors in SCons

If build fail report specific message. Import this module and add the following lineis to your SConstruct:

import atexit
from madagascarRecipes.errorReport import print_build_failures

Call error message by the following:

atexit.register(print_build_failures,message)

It will call function print_build_failures to report message variable that should be a string with the error message to be reported
'''

if __name__ == "__main__":
	print(__doc__)
	exit()

__author__="Rodolfo Dirack <rodolfo_profissional@hotmail.com>"
__version__="1.0"

def print_build_failures(message):
	'''
	Print error message when build fail
	:param message: string, error message
	'''
	from SCons.Script import GetBuildFailures
	for bf in GetBuildFailures():
		print("BUILD ERROR REPORT".center(40,'*'))
		print("FAILED BUILD: %s" % (bf.node))
		print("MESSAGE REPORT".center(40,'*'))
		print("%s" % (message))

