# Makefile 
# 
# Purpose: Automate this experiment building
# 
# Site: https://www.geofisicando.com
# 
# Version 1.0
# 
# Programmer: Rodolfo A C Neves (Dirack) 24/12/2022
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>

all:	build keep clean

build:	SConstruct
	scons trueModel.rsf && scons -j4 interpolatedDataCube2.rsf nhi=50 && scons stackedSection.rsf nhi=50

keep:	backup
	<interpolatedDataCube2.rsf sfput --out=stdout > backup/interpolatedDataCube.rsf && <stackedSection.rsf sfput --out=stdout > backup/stackedSection.rsf && <parametersCube.rsf sfput --out=stdout > backup/parametersCube.rsf && <trueModel.rsf sfput --out=stdout> backup/trueModel.rsf

backup:
	mkdir -p backup

clean:	SConstruct
	scons -c
