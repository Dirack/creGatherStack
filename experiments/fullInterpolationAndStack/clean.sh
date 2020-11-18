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

TMP='creGatherCube-m0-* creGather-m0-* creGatherTrace-m0-* creMcoordinate-m0-* creMhCoordinates-m0-* creStackedTrace-m0-* creTimeCurve-m0-* creTimeCurveCube-m0-* creTimeCurveTrace-m0-* crsParameters-m0-*'

for i in $TMP
do
	$RSFROOT/bin/sfrm "$i"
	#echo "$i"
done

echo "clean finished..."

exit 0
