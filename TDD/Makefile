# Makefile
#
# Purpose: Run c test with Unity Unity.
# 
# Site: https://dirack.github.io
# 
# Version 1.0
# 
# Programer: Rodolfo A C Neves (Dirack) 21/09/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Uncomment the line below to run on a CENTOS system. Or call make as 'make CENTOS=1'
#CENTOS=1 

all:	Test_rnip2vrms_lib.x

%.x:	%.c
ifdef CENTOS
	gcc -I$$RSFSRC/include -I/usr/include/openblas -L$$RSFSRC/lib $< ../rnip2vrms_lib.c Unity/unity.c -o $@ -lm -lrsf -lopenblas -g
	./$@
	rm $@
else
	gcc -I$$RSFSRC/include -L$$RSFSRC/lib $< ../rnip2vrms_lib.c Unity/unity.c -o $@ -lm -lrsf 
	./$@
	rm $@
endif
