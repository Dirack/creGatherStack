#!/bin/bash
#
# install_recipes.sh (Shell Script)
# 
# Purpose: Download Madagascar recipes in the local version 
# of the Madagascar package.
# 
# Site: https://dirack.github.io
# 
# Version 1.0
# 
# Programer: Rodolfo A C Neves (Dirack) 20/09/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

wget -c -P "$RSFSRC/book/Recipes" https://raw.githubusercontent.com/ahay/src/master/book/Recipes/kimodel.py 
wget -c -P "$RSFSRC/book/Recipes" https://raw.githubusercontent.com/ahay/src/master/book/Recipes/pefInterpolation.py
