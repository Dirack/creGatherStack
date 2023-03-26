#!/bin/bash
#
# build_dockerfile.sh (Shell Script)
# 
# Purpose: Generate the dockerfile to new release package deploy.
# 
# This script uses deploy/Dockerfile as a template to generate the
# Dockerfile used in the package deploy.
#
# Site: https://dirack.github.io
# 
# Version 1.0
# 
# Programer: Rodolfo A C Neves (Dirack) 14/10/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

VERSION=$(cat VERSION.md)
cat deploy/Dockerfile | sed 's/\[\[\[VERSION\]\]\]/'"$VERSION"'/' > Dockerfile.deploy
