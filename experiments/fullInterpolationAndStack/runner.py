#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# runner.py (Python)
# 
# Objetivo: Script to run this experiment.
# 
# Site: https://dirack.github.io
# 
# Versão 1.0
# 
# Programador: Rodolfo A C Neves (Dirack) 18/11/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# Licença: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

import os

status=os.system('scons -j3')

if status==0:
	os.system('./clean.sh')
