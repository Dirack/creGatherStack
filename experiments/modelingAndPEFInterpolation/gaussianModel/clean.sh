#!/bin/bash
#
# clean.sh (Shell Script)
# 
# Purpose: Clean temporary files after build.
# 
# Site: https://dirack.github.io
# 
# Version 1.0
# 
# Programer: Rodolfo A C Neves (Dirack) 19/09/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

TMP='gaussianReflector.rsf reflectorDip.rsf dataCube-offsetGather-* dataCube-interpolatedGather-* dataCube-pefCoeficients-* dataCube-resampledGather-* interpolatedDataCube-offsetGather-* interpolatedDataCube-interpolatedGather-* interpolatedDataCube-pefCoeficients-* interpolatedDataCube-resampledGather-* dataCube-a* dataCube-b* *-mask* interpolatedDataCube-a* interpolatedDataCube-b* *-zeroedGather*'

for i in $TMP
do
	$RSFROOT/bin/sfrm "$i"
	#echo "$i"
done
