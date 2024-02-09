# Makefile 
# 
# Purpose: Automate all experiments building
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

BUILD = model1
exp = model1
nitf = 2

all:	$(BUILD)
	$(foreach var,$(BUILD),make -C $(var);)

pick:	picking
	scons -C picking -c
	scons -C picking exp=$(exp) nitf=$(nitf)
	@echo "--- Result $(exp) ---"
	@echo "--- T0 ---"
	@ls picking/t0s*.rsf | xargs -I% bash -c "sfdisfil <% && echo"
	@echo "--- M0 ---"
	@ls picking/m0s*.rsf | xargs -I% bash -c "sfdisfil <% && echo"
	@echo "--- RN ---"
	@ls picking/rns*.rsf | xargs -I% bash -c "sfdisfil <% && echo"
	@echo "--- RNIPS ---"
	@ls picking/rnips*.rsf | xargs -I% bash -c "sfdisfil <% && echo"
	@echo "--- BETA ---"
	@ls picking/betas*.rsf | xargs -I% bash -c "sfdisfil <% && echo"

help:
	@echo "--- Automate experiments building ---"
	@echo "Use 'make' to build all experiments listed in BUILD variable"
	@echo "BUILD = $(BUILD)"
	@echo "Or make your own build list with 'make BUILD="model1 model2 ..."'"
	@echo
	@echo "--- Traveltime picking ---"
	@echo After building the experiment you can run traveltime picking and parameters search
	@echo "Use 'make pick exp="model1" nitf=2'"
	@echo Use whatever experiment you want to use in 'exp' variable
	@echo "And configure the number of model interfaces in 'nitf' variable"
