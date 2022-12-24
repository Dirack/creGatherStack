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

BUILD= model1

all:	$(BUILD)
	$(foreach var,$(BUILD),make -C $(var);)
