# Dockerfile
# 
# Purpose: Deploy of this package.
# 
# Site: https://dirack.github.io
# 
# Programer: Rodolfo A C Neves (Dirack) 12/10/2020
# 
# Email: rodolfo_profissional@hotmail.com
# 
# License: GPL-3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>.

# Madagascar environment with pre-configured dependencies
FROM ghcr.io/dirack/vfsa:1.1.1

# Define Repository location and Version
ENV VERSION="[[[VERSION]]]"
ENV LOCATION="/home/tryitondocker/madagascar-3.0/user/creGatherStack"

LABEL maintainer="Rodolfo A C Neves (Dirack)"
LABEL email="rodolfo_profissional@hotmail.com"
LABEL site="https://dirack.github.io"
LABEL version="[[[VERSION]]]"

USER root
ADD "/" "$LOCATION"
RUN cd "$LOCATION" && scons && cd "/home/tryitondocker/madagascar-3.0" && scons install && chown tryitondocker.tryitondocker "$LOCATION" && rm -rf /home/tryitondocker/README.md 

USER tryitondocker
RUN wget -c -P /home/tryitondocker/ https://raw.githubusercontent.com/Dirack/myMarkdownTemplates/master/CREGATHERSTACK/README.md && sed -i 's/\[\[\[PKGVERSION\]\]\]/'"$VERSION"'/' /home/tryitondocker/README.md
WORKDIR /home/tryitondocker
