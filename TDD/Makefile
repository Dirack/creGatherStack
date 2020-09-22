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

all:	Test_rnip2vrms_lib.x

%.x:	%.c
	gcc -I/home/dirack/madagascar-3.0/include -L/home/dirack/madagascar-3.0/lib $< ../rnip2vrms_lib.c Unity/unity.c -o $@ -lm -lrsf
	./$@
