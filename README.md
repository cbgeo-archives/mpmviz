# mpm-viz
> [CB-Geo Computational Geomechanics Research Group](https://www.cb-geo.com)

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/cb-geo/mpm-viz/develop/license.md)
[![Developer docs](https://img.shields.io/badge/developer-docs-blue.svg)](http://cb-geo.github.io/mpm-viz)
[![User docs](https://img.shields.io/badge/user-docs-blue.svg)](https://mpm-viz.cb-geo.com/)
[![CircleCI](https://circleci.com/gh/cb-geo/mpm-viz.svg?style=svg)](https://circleci.com/gh/cb-geo/mpm-viz)
[![codecov](https://codecov.io/gh/cb-geo/mpm-viz/branch/develop/graph/badge.svg)](https://codecov.io/gh/cb-geo/mpm-viz)
[![](https://img.shields.io/github/issues-raw/cb-geo/mpm-viz.svg)](https://github.com/cb-geo/mpm-viz/issues)
[![Project management](https://img.shields.io/badge/projects-view-ff69b4.svg)](https://github.com/cb-geo/mpm-viz/projects/)


## Install dependencies

* Docker image for CB-Geo mpm-viz code [https://hub.docker.com/r/cbgeo/mpm](https://hub.docker.com/r/cbgeo/mpm)

* Instructions for running mpm-viz docker container: [https://github.com/cb-geo/docker-mpm/blob/master/README.md](https://github.com/cb-geo/mpm-container/blob/master/README.md).

### Prerequisite packages
> The following prerequisite packages can be found in the docker image:

* [Boost](http://www.boost.org/)
* [HDF5](https://support.hdfgroup.org/HDF5/)

#### Optional
* [VTK](https://www.vtk.org/)

## Compile
> See https://mpm-viz-doc.cb-geo.com/ for more detailed instructions. 

0. Run `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ /path/to/CMakeLists.txt`.

1. Run `make clean && make -jN` (where N is the number of cores).

### Compile mpm-viz or mpm-viztest

* To compile either `mpm-viz` or `mpm-viztest` alone, run `make mpm-viz -jN` or `make mpm-viztest -jN` (where N is the number of cores).

### Compile without tests [Editing CMake options]

To compile without tests run: `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -Dmpm-viz_BUILD_TESTING=Off /path/to/CMakeLists.txt`.

### Run tests

0. Run `./mpm-viztest -s` (for a verbose output) or `ctest -VV`.
