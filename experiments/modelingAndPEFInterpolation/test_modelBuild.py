#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# test_modelBuild.py (Python)
#
# Purpose: Test model building with SCons.
# 
# Rum with: python -m unittest test_modelBuild
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

import unittest
import subprocess

class TestScons(unittest.TestCase):
	'''
	Unit tests of the model building
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
