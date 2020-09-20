#!/bin/bash
#
# test_travis_docker.sh (Shell Script)
# 
# Purpose: To start a docker container to be used by 
# travis CI in unit tests.
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

docker run -t -v $PWD:/root/madagascar-3.0/user/creGatherStack \
dirack/ambientemadagascar:1.0 bash -c 'RSFROOT=/root/madagascar RSFSRC=/root/madagascar-3.0 CREROOT=/root/madagascar-3.0/user/creGatherStack && cd $RSFSRC && source env.sh && cd $CREROOT && ./install_recipes.sh && scons && cd $RSFSRC && scons install && cd $CREROOT/TDD/ && python -m unittest '$1
      
