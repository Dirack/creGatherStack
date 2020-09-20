#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# test_multiLayerModelBuild.py (Python)
#
# Purpose: Test model building with SCons.
# 
# Rum with: python -m unittest test_multiLayerModelBuild
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
	Unit tests of the multi layer model building
	'''

	def test_multiLayerModeling(self):
		'''
		Test of the building of the multi layer model
		'''
		result = subprocess.call('cd multiLayerModel && scons multiLayerDataCube.rsf',shell=True)
		self.assertEqual(result,0,'FAILED: multi Layer modeling failed!')

	def test_multiLayerPefInterpolation(self):
		'''
		Test of the PEF interpolation step of the seimic data cube
		modeled with the multi layer model
		'''
		result = subprocess.call('cd multiLayerModel && scons -j3',shell=True) 
		self.assertEqual(result,0,'FAILED: multi layer PEF interpolation failed!')
