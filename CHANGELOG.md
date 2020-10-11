# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## UNRELEASED - Contribute with the next version

## [v2.2.0](https://github.com/Dirack/creGatherStack/compare/v2.1.0-beta.1...develop/2.2) - 2020-10-11

## RELEASED

## [v2.1.0-beta.1](https://github.com/Dirack/creGatherStack/releases/tag/v2.1.0-beta.1) (Beta) - 2020-10-11

## Added

- New program rnip2vmrs to estimate VRMS from RNIP values Resolve [#54](https://github.com/Dirack/creGatherStack/issues/54) [25136ea](https://github.com/Dirack/creGatherStack/commit/25136ea) [6a7b0c9](https://github.com/Dirack/creGatherStack/commit/6a7b0c9)

- Use sfrnip2vrms program in all experiments [#55](https://github.com/Dirack/creGatherStack/issues/55) [e031436](https://github.com/Dirack/creGatherStack/commit/e031436)

## Modified

- CRE Gather stack is now a function of creGatherStack.py recipe, and allow CDS option Resolve [#59](https://github.com/Dirack/creGatherStack/issues/59) [af9c8db](https://github.com/Dirack/creGatherStack/commit/af9c8db)

- Unit test directory: TDD directory [39eace3](https://github.com/Dirack/creGatherStack/commit/39eace3)

## Changed

- Update README with references to the changelog and wiki instead of the release history section [475e679](https://github.com/Dirack/creGatherStack/commit/475e679)

## [v2.0.0](https://github.com/Dirack/creGatherStack/releases/tag/v2.0) (Stable) - 2020-09-21

### Added

- Travis CI test  [43a01fe](https://github.com/Dirack/creGatherStack/commit/43a01fe)
- Travis CI automatic test Resolve [#8](https://github.com/Dirack/creGatherStack/issues/8) [43a58c3](https://github.com/Dirack/vfsa/commit/43a58c3)
- Establish kimodel.py and pefInterpolation.py as dependencies Resolve [#43](https://github.com/Dirack/creGatherStack/issues/43) [44d8eb9](https://github.com/Dirack/vfsa/commit/44d8eb9)
- Define aperture=20 for sfgetcregather and correct bug Resolve [#49](https://github.com/Dirack/creGatherStack/issues/49) [feb03c1](https://github.com/Dirack/vfsa/commit/feb03c1) [405199d](https://github.com/Dirack/vfsa/commit/405199d)
- Use explicit dependency to avoid building errors Resolve [#44](https://github.com/Dirack/creGatherStack/issues/44) [35aa3c9](https://github.com/Dirack/vfsa/commit/35aa3c9)
- Allow experiments SConstructs to receive parameters from the command line [6edd9ef](https://github.com/Dirack/creGatherStack/commit/6edd9ef)

## [v1.0.0-beta.1](https://github.com/Dirack/creGatherStack/releases/tag/v1.0-beta.1) (Beta) - 2020-09-12

### Added

- New usage example: Multi-layer model, in pull request [#42](https://github.com/Dirack/creGatherStack/issues/42) Resolve [#37](https://github.com/Dirack/vfsa/issues/37) [cf1568e](https://github.com/Dirack/vfsa/commit/cf1568e)

## Removed

- Remove pefInterpolation example Resolve [#45](https://github.com/Dirack/creGatherStack/issues/45) [c095796](https://github.com/Dirack/vfsa/commit/c095796)

## Fixed

- Avoid CMP coordinate to get out of of model bounds correct bug [#38](https://github.com/Dirack/creGatherStack/issues/38) [3f6b469](https://github.com/Dirack/vfsa/commit/3f6b469) [72ed7c1](72ed7c1)

- Avoid segmentation fault in sfvfsacrsnh, correct bug [#39](https://github.com/Dirack/creGatherStack/issues/39) [ed9043d](https://github.com/Dirack/vfsa/commit/ed9043d)

## [v0.1.2-alpha.1](https://github.com/Dirack/creGatherStack/releases/tag/v0.1.2-alpha.1) (Development) - 2020-09-12

- Test CRE stacking with CDS condition applied to the Non-hyperbolic CRS approximation [#26](https://github.com/Dirack/creGatherStack/issues/26) [d20c1c1](https://github.com/Dirack/vfsa/commit/d20c1c1)

- Test of the CRE stacking using CRE traveltime approximation [#26](https://github.com/Dirack/creGatherStack/issues/26) [1a0e765](https://github.com/Dirack/vfsa/commit/1a0e765)

## [v0.1.1-alpha.1](https://github.com/Dirack/creGatherStack/releases/tag/v0.1.2-alpha.1) (Development) - 2020-04-21

## Added

- CRE stacking with CDS condition (RNIP=RN) in non-hyperbolic traveltime approximation [#3](https://github.com/Dirack/creGatherStack/issues/3) [4ad17bb](https://github.com/Dirack/vfsa/commit/4ad17bb)

- Define functions in creStack.py to modeling and interpolation steps [#9](https://github.com/Dirack/creGatherStack/issues/9) [73a38c0](https://github.com/Dirack/vfsa/commit/73a38c0)

## Removed

- Delete useless usage examples Resolve [#34](https://github.com/Dirack/creGatherStack/issues/34) [0fe314e](https://github.com/Dirack/vfsa/commit/0fe314e)

- Remove vfsa programs from package, establish them as a dependency Resolve [#22](https://github.com/Dirack/creGatherStack/issues/22) [d2f9ddf](https://github.com/Dirack/vfsa/commit/d2f9ddf)

## [v0.1.0-alpha.1](https://github.com/Dirack/creGatherStack/releases/tag/v0.1.2-alpha.1) (Development) - 2020-04-21

## Added

- Gaussian reflector Kirchoff modeling [aff870d](https://github.com/Dirack/creGatherStack/commit/aff870d)

- zero offset CRS parameters optimization with VFSA [14fcbdf](https://github.com/Dirack/creGatherStack/commit/14fcbdf)

- PEF interpolation of the data cube to increase CMP sampling [8d9a44f](https://github.com/Dirack/creGatherStack/commit/8d9a44f)

- Program _sfcretrajec_ to calculate CRE trajectory for RNIP and BETA [8b54e94](https://github.com/Dirack/creGatherStack/commit/8b54e94)

- Program _sfgetcregather_ to build the CRE Gather [2872fdd](https://github.com/Dirack/creGatherStack/commit/2872fdd)

- Program _sfgetcretimecurve_ to build the CRE traveltime curve [da8b919](https://github.com/Dirack/creGatherStack/commit/da8b919)

- Program _sfcrestack_ to CRE stacking [5c4e633](https://github.com/Dirack/creGatherStack/commit/5c4e633)

- Jupyter Notebook of the Kirchhoff modeling step [40ac351](https://github.com/Dirack/creGatherStack/commit/40ac351)

- Scratch of a reproducible paper for modeling step [494faf2](https://github.com/Dirack/creGatherStack/commit/494faf2)

## Fixed

- Correct bug in alpha parameter bounds in the program Mcretrajec.c [699f169](https://github.com/Dirack/creGatherStack/commit/699f169)

