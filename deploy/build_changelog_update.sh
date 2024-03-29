#!/bin/bash
#
# build_changelog_update.sh (Shell Script)
# 
# Purpose: Update the changelog with the new release.
# 
# This script uses tag.deploy file generated by build_release_message.sh
# script, and parses it to a CHANGELOG.deploy template file.
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

sed -n '1,/## UNRELEASED/p' CHANGELOG.md > CHANGELOG.deploy
echo -e '\n ## [TODO](https://github.com/Dirack/creGatherStack/compare/TODO...develop/TODO) - AAAA-MM-DD
\n ## RELEASED \n' >> CHANGELOG.deploy
cat tag.deploy >> CHANGELOG.deploy
sed -n '1,/## RELEASED/!p' CHANGELOG.md >> CHANGELOG.deploy
