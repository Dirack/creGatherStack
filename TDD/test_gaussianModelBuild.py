#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# test_gaussianModelBuild.py (Python)
#
# Purpose: Test gaussian model building with SCons.
# 
# Rum with: python -m unittest test_gaussianModelBuild
#
# Site: https://dirack.github.io
# 
# Version 2.0
#
# Programer: Rodolfo A. C. Neves (Dirack) 20/09/2020
#
# Email: rodolfo_profissional@hotmail.com
#
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

import unittest
import subprocess
import os

# Do not allow test order sorting
unittest.TestLoader.sortTestMethodsUsing = None

# Change to modeling directory
currentDir = os.getcwd()
path = os.path.join(currentDir,os.pardir)
path = os.path.abspath(path)+'/experiments/'
os.chdir(path)

class TestScons(unittest.TestCase):
	'''
	Unit tests of the gaussian model building
	'''

	def test_gaussianReflectorModeling(self):
		'''
		Test the building of the gaussian reflector in
		a linear velocity model
		'''
		result = subprocess.call('cd modelingAndPEFInterpolation/gaussianModel && scons dataCube.rsf',shell=True)
		self.assertEqual(result,0,'FAILED: gaussian reflector modeling failed!')


	def test_gaussianReflectorPefInterpolation(self):
		'''
		Test of the PEF interpolation step of the seismic data cube
		modeled with the gaussian reflector linear velocity model.
		'''
		result = subprocess.call('cd modelingAndPEFInterpolation/gaussianModel && scons -j3 nhi=1',shell=True)
		self.assertEqual(result,0,'FAILED: gaussian reflector PEF interpolation failed!')

	def test_fullInterpolationAndStack(self):
		'''
		Unit test of the fullInterpolationAndStack experiment
		'''

		result = subprocess.call('cd fullInterpolationAndStack && scons -j3 nm0=2 nt0=3',shell=True)
		self.assertEqual(result,0,'FAILED: experiment fullInterpolationAndStack failed!')

	def test_fullInterpolationAndStackCDS(self):
		'''
		Unit test of the fullInterpolationAndStackCDS experiment
		'''
		result = subprocess.call('cd fullInterpolationAndStackCDS && scons -j3 nm0=2 nt0=3',shell=True)
		self.assertEqual(result,0,'FAILED: experiment fullInterpolationAndStackCDS failed!')


