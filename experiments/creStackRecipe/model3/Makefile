# Makefile
# 
# Objetivo: Run the full experiment.
# 
# Site: https://dirack.github.io
# 
# Versão 1.0
# 
# Programador: Rodolfo A C Neves (Dirack) 05/08/2021
# 
# Email: rodolfo_profissional@hotmail.com
# 
# Licença: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

all:
	scons -f SConscript -j 4 nhi=30
	scons -j 4 aperture=30

clean:
	scons -f SConscript -c
	scons -c
	rm *.rsf

help:
	@echo "Run this full experiment with 'make'"
