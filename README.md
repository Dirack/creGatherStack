# cre-gather-interpolation (Madagascar)

[Developed to Madagascar package, version 2.0.](http://www.ahay.org/wiki/Main_Page)

> Common Reflection Element (CRE) Gather interpolation using adaptative 
> pretitive error filters (PEF) and Very Fast Simulated Aneeling (VFSA) global optimization.

A set of seismic traces that belong to a specific CRE trajectory, for a given RNIP and BETA form a CRE Gather:
So, CRE Gather interpolation algorithm uses Very Fast Simulated Anneling (VFSA) global optimization 
in order to get RNIP and BETA parameters to calculate CRE trajectory. Also increase data sampling, 
interpolating original seismic data with adaptative preditive error filters (PEF). 
Get all traces in the interpolated seismic data that belong to the CRE trajectory previously calculated.

![Interpolated CRE Gather](https://github.com/Dirack/creGatherInterpolation/blob/master/images/hugeStackedSection.jpeg)

This is a package with several C programs adpted to the Madagascar seismic processing package. The mains objective of
those programs is to model a cube of seismic data organized in CMP x Offset X Time coordinates and extract the zero offset
CRS parameters (RN, RNIP, BETA) from it. These parameters can be used to obtain the CRE Gathers from the data cube after
an interpolation process using PEF. With those gathers, someone can obtain the stacked section.

The main advantage of the CRE stacking is that allows to get the macrovelocity model and stacked section without the NMO
velocity analisys. And it can be used in a inversion process, such as tomography algorithms, in order to get the velocity
model.

#### Schematic representation of the CRE Gather geometry for a curved reflector:

The CRE traveltime aproximation is derived from geometric considerations in a constant velocity model in the 
neighborhood of a normal ray. Bellow, an schematic representation of a CRE gather geometry. Someone shold realize
that the sources s_i and receivers r_i have different CMP's and Offset, distributed assimetrically along the aquisition
surface caused by reflector's curvature. Though, _they have the same reflection point_ in the reflector surface and
are associated to a normal ray with defined RNIP and BETA parameters.

<img src="https://github.com/Dirack/creGatherInterpolation/blob/master/images/cre.png" width="800">

#### Example of a interpolated CRE Gather with a calculated CRE traveltime curve:

That's an example of a CRE gather obtained with the programs in that package (in yellow there is the stacking curve).
The CRE stacking curve can be determined with the help of RNIP and BETA parameters and near surface velocity v0 for
all Offset and CMP positions.

![Interpolated CRE Gather](https://github.com/Dirack/creGatherInterpolation/blob/master/images/interpolacao4.jpeg)

## Development setup

You need to have the actual Madagascar package stable release installed on your computer. Please follow the
[Installing Madagascar page](http://www.ahay.org/wiki/Installation) in the official documentation.

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

If you have any doubt about this process, please reffer to the oficial documentation in 
[Adding_new_programs_to_Madagascar](http://www.ahay.org/wiki/Adding_new_programs_to_Madagascar)

## Usage example

A few motivating and useful examples of how that product can be used. 
_For examples and usage, please refer to the [Wiki](https://github.com/Dirack/cre-gather-interpolation/wiki)._

We also have many SConstruct examples in this repository in the
[experiments directory](https://github.com/Dirack/cre-gather-interpolation/tree/documentation/0.1/experiments)

## Release History
   
* [v1.0-beta.1](https://github.com/Dirack/cre-gather-interpolation/releases/tag/creStackedSection) (Beta - In progress)
  
* [v0.1-beta.1](https://github.com/Dirack/creGatherInterpolation/releases/tag/v0.1-beta.1) - (Instable)

[See the complete history decription in our wiki](https://github.com/Dirack/creGatherInterpolation/wiki/Release-history)

## Meta

Rodolfo Dirack – [@dirack](https://github.com/Dirack) – rodolfo_profissional@hotmail.com

Distributed under the GPL3 license. See ``LICENSE`` for more information.

[cre-gather-interpolation main page](https://github.com/Dirack/cre-gather-interpolation)

## Contributing

1. Fork it (<https://github.com/Dirack/cre-gather-interpolation/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

#### Important: The commit history should be clear, with commit mesages around one or two paraghraps describing your modifications. Pull Requests with unsatisfactory commit history will be rejected.
