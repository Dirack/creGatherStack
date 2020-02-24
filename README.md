# cre-gather-interpolation (Madagascar)

> Common Reflection Element (CRE) Gather interpolation using adaptative 
> pretitive error filters (PEF) and Very Fast Simulated Aneeling (VFSA) global optimization.

[Developed to Madagascar package, version 2.0.](http://www.ahay.org/wiki/Main_Page)

This is a package with several C programs adpted to the Madagascar seismic processing package. The mains objective of
those programs is to model a cube of seismic data organized in CMP x Offset X Time coordinates and extract the zero offset
CRS parameters (RN, RNIP, BETA) from it. These parameters can be used to obtain the CRE Gathers from the data cube after
an interpolation process using PEF. With those gathers, someone can obtain the stacked section.

The main advantage of the CRE stacking is that allows to get the macrovelocity model and ...

#### Schematic representation of the CRE Gather geometry for a curved reflector:

<img src="https://github.com/Dirack/qualificacao-doutorado/blob/master/images/cre.png" width="1000">

#### Example of a interpolated CRE Gather with a calculated CRE traveltime curve:

![Interpolated CRE Gather](https://github.com/Dirack/qualificacao-doutorado/blob/master/images/interpolacao4.jpeg)

## Development setup

You need to have the actual Madagascar package stable release installed on your computer. Please follow the
[Installing Madagascar page](http://www.ahay.org/wiki/Installation) in the official documentation.

## Installation

After Madagascar installing process, you need to install the programs of this repository in your local Madagascar users
directory. You can compile and install as any Madagascar program. 
Run 'scons' on your Madagascar repository to compile:

```shell
~$ scons
```

If you need a SConstruct to compile, use 
[this example](https://github.com/Dirack/cre-gather-interpolation/blob/documentation/0.1/SConstruct).

And install it on your local Madagascar installation:

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

* 1.1 - Stable release
    * The first proper release
    * Complete interpolation programs in the CRE domain
* [0.0.1](https://github.com/Dirack/cre-gather-interpolation/releases/tag/creStackedSection) - Work in progress
    * Beta version of the CRE stacking process example: In the examples/getCreGathers2 directory is the 
    example of a cre stacking process. It needs the interpolatedDataCube build in the example/getCreGathers/SConstruct.
    CRE stacking is done through a cre traveltime curve in the cre Gather domain.

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
