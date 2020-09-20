#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# test_experiments.py (Python)
#
# Purpose: Test model building with SCons.
# 
# Rum with: python -m unittest test_experiments
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
	Test of the experiments
	'''

	def test_fullInterpolationAndStack(self):
		'''
		Unit test of the fullInterpolationAndStack experiment
		'''
		result = subprocess.call('cd fullInterpolationAndStack && scons -j3',shell=True)
		self.assertEqual(result,0,'FAILED: experiment fullInterpolationAndStack failed!')

	def test_fullInterpolationAndStackCDS(self):
		'''
		Unit test of the fullInterpolationAndStackCDS experiment
		'''
		result = subprocess.call('cd fullInterpolationAndStackCDS && scons -j3',shell=True)
		self.assertEqual(result,0,'FAILED: experiment fullInterpolationAndStackCDS failed!')

	def test_multiLayerModel(self):
		'''
		Unit test of the multiLayerModel experiment
		'''
		result = subprocess.call('cd multiLayerModel/cre && scons -j3',shell=True)		
		self.assertEqual(result,0,'FAILED: experiment multiLayerModel failed!')

	def test_multiLayerModelCDS(self):
		'''
		Unit test of the multiLayerModel CDS experiment
		'''
		result = subprocess.call('cd multiLayerModel/cds && scons -j3',shell=True)
		self.assertEqual(result,0,'FAILED: experiment multiLayerModel CDS failed!')
