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

# Change to modeling directory
currentDir = os.getcwd()
path = os.path.join(currentDir,os.pardir)
path = os.path.abspath(path)+'/experiments/modelingAndPEFInterpolation/'
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
		result = subprocess.call('cd gaussianModel && scons dataCube.rsf',shell=True)
		self.assertEqual(result,0,'FAILED: gaussian reflector modeling failed!')


	def test_gaussianReflectorPefInterpolation(self):
		'''
		Test of the PEF interpolation step of the seismic data cube
		modeled with the gaussian reflector linear velocity model.
		'''
		result = subprocess.call('cd gaussianModel && scons -j3',shell=True)
		self.assertEqual(result,0,'FAILED: gaussian reflector PEF interpolation failed!')
