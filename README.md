# Common Reflection Element (CRE) Stack

> This package uses Pretictive Adaptative Error Filters (PEF) interpolation and Very Fast Simulated Aneeling (VFSA) global optimization.

[Developed to Madagascar package, version 3.0.](http://www.ahay.org/wiki/Main_Page)

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![Build Status](https://travis-ci.org/Dirack/creGatherStack.svg?branch=master)](https://travis-ci.org/Dirack/creGatherStack)

![Interpolated CRE Gather](https://github.com/Dirack/creGatherInterpolation/blob/master/images/hugeStackedSection.jpeg)

###### This an example of a CRE stacked section.

This is a package with several C programs and SConstructs adapted to the Madagascar seismic processing package. The mains objective of those programs is to obtain the zero offset section using CRE stacking. The main advantage of the CRE stacking is that allows to get the macrovelocity model and stacked section without the NMO velocity analisys. And it can be used in a velocity inversion process, such as tomography algorithms, in order to get the depth velocity model.

The CRE stack process is done defining the seismic traces that belong to the CRE trajectories in a seismic data cube (seismic data organized in CMP x Offset X Time coordinates) for each (m0, t0) pairs in the stacked section. The set of seismic traces that belong to a CRE trajectory form a CRE Gather. The stacking throughout this CRE gathers using the CRE traveltime approximation and the assignment of this amplitude summation to the (m0,t0) pairs in the stacked section is the core of the CRE stacking process.

* For more theoretical details of CRE Gather stack please download and read this article:
  [The common reflecting element CRE method revisited (2000)](https://github.com/Dirack/creGatherStack/files/5213160/The_common_reflecting_element_CRE_method_revisited_cruz2000.pdf)
 
![Interpolated CRE Gather](https://github.com/Dirack/creGatherInterpolation/blob/master/images/interpolacao4.jpeg)

###### This is an example of a CRE gather and the CRE stacking curve (in yellow).

#### CRE stack uses Very Fast Simulated Anneling (VFSA) global optimization

As explained above, a set of seismic traces that belong to a specific CRE trajectory form a CRE Gather. Those trajectories are defined for each (m0,t0) pairs in the stacked section and for a given RNIP and BETA parameters from the zero offset Common Reflection Surface (CRS) process. These parameters are extracted from the seismic data cube using Very Fast Simulated Anneling (VFSA) global optimization algorithm.

For more details about VFSA, please look at the [VFSA package repository](https://github.com/Dirack/vfsa)

#### CRE stack uses Predictive Adaptative Error Filters (PEF) interpolation:

CRE stack also needs increased CMP data sampling through Predictive Adaptative Error Filters (PEF) interpolation.
This happen because the CRE traveltime aproximation is derived from geometric considerations in a constant velocity model in the 
neighborhood of a normal ray and the sources (s_i) and receivers (r_i) in this geometry are distributed assimetrically along the aquisition
surface because of the reflector's curvature. Besides that, the reflection rays in the CRE gather _have the same reflection point_ and
are associated with the same normal ray defined by RNIP and BETA parameters (look at the Figure bellow, an schematic representation of a CRE gather geometry).

<img src="https://github.com/Dirack/creGatherInterpolation/blob/master/images/cre.png" width="800">

## Development setup

- Madagascar package (3.0)

- VFSA package (1.1.1)

You need to have the actual Madagascar package stable release installed on your computer. Please follow the
[Installing Madagascar page](http://www.ahay.org/wiki/Installation) in the official documentation. You can install
Madagascar automatically from Shell Script using program _madagainstall_ from [Shellinclude library](https://github.com/Dirack/Shellinclude/tree/v1.2.2-beta.1).

You also need programs sfvfsacrsnh and sfnhcrssurf from version 
[v1.1.1 of vfsa package](https://github.com/Dirack/vfsa/tree/v1.1.1). Please
install them in your local version of Madagascar before using this package.

## Installation

After Madagascar installing process, you need to install the programs of this repository in your local Madagascar user's
directory. You can compile and install it as any other Madagascar program. 
Usually, Madagascar keeps the path of your local copy source files in the $RSFSRC environment variable. You can
show that on a bash terminal using 'echo' command:

```sh
~$ echo "$RSFSRC"
```

And Madagascar will install executable files on your $RSFROOT directory. You can show that environment variable
with 'echo' too:

```sh
~$ echo "$RSFROOT"
```

Madagascar stores user programs in $RSFSRC/user directory. So, you can create a new directory or put this
repository inside that directory. In this repository, such as every user's repository in Madagascar, we have a compilation 
[SConstruct](https://github.com/Dirack/vfsa/blob/master/SConstruct) that compile the C programs.
Run 'scons' on your $RSFSRC/user/creGatherInterpolation repository to compile it:

```shell
~$ scons
```

And run 'scons install' in the top directory of your local Madagascar installation 
(the directory path in your $RSFSRC variable):

```shell
~$ sudo scons install
```

If you have any doubt about this process, please reffer to the Madagascar oficial documentation in 
[Adding_new_programs_to_Madagascar](http://www.ahay.org/wiki/Adding_new_programs_to_Madagascar)

## Usage example

A few motivating and useful examples of how that product can be used. 
_For more examples and details, please refer to the [Wiki](https://github.com/Dirack/cre-gather-interpolation/wiki)._

We also have many SConstruct examples in this repository in the
[experiments directory](https://github.com/Dirack/creGatherStack/tree/master/experiments)

## Release History

* [v2.0](https://github.com/Dirack/creGatherStack/releases/tag/v2.0) - (Stable)

* [v1.0-beta.1](https://github.com/Dirack/creGatherStack/releases/tag/v1.0-beta.1) - (Beta)
  
* [v0.1.2-alpha.1](https://github.com/Dirack/creGatherStack/releases/tag/v0.1.2-alpha.1) - (Development)

[See the complete history decription in our wiki](https://github.com/Dirack/creGatherStack/wiki/Release-history)

## Meta

Rodolfo Dirack – [@dirack](https://github.com/Dirack) – rodolfo_profissional@hotmail.com

Distributed under the GPL3 license. See ``LICENSE`` for more information.

[creGatherStack main page](https://github.com/Dirack/creGatherStack)

## Contributing

1. Fork it (<https://github.com/Dirack/creGatherStack/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

###### Important contribution tip: The commit history should be clear, with commit mesages around one or two paraghraps describing your modifications. Pull Requests with unsatisfactory commit history will be rejected.
