#!/bin/bash
#
# test_travis_docker.sh (Shell Script)
# 
# Purpose: Start a docker container, with Madagascar and all
# dependencies pre configured, to be used by 
# travis CI in unit tests.
#
# Steps: 
#
# - Generate a docker container with this directory installed in the
# $RSFSRC/user directory in the container of the cregatherstack:1.0.0 image
# where all dependencies are installed and pre configured.
#
# - Load environment variables, CREROOT.
#
# - Go to creGatherStack/TDD directory to run the tests or a command
# passed through $1 variable to this script.
# 
# Site: https://dirack.github.io
# 
# Programer: Rodolfo A C Neves (Dirack) 20/09/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

cd $RSFSRC/user/creGatherStack/TDD

docker run -t -v $PWD:/root/madagascar-3.0/user/creGatherStack \
dirack/ambientetestecregatherstack:1.0.0 bash -c 'CREROOT=/root/madagascar-3.0/user/creGatherStack && cd $RSFSRC && source env.sh && cd $CREROOT && scons && cd $RSFSRC && scons install && cd $CREROOT/TDD/ && '"$@"
      
