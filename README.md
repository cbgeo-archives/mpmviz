# MPM Visualization toolkit (CB-Geo mpmviz)
> [CB-Geo Computational Geomechanics Research Group](https://www.cb-geo.com)

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/cb-geo/mpmviz/develop/license.md)
[![Developer docs](https://img.shields.io/badge/developer-docs-blue.svg)](http://cb-geo.github.io/mpmviz)
[![User docs](https://img.shields.io/badge/user-docs-blue.svg)](https://mpmviz.cb-geo.com/)
[![CircleCI](https://circleci.com/gh/cb-geo/mpmviz.svg?style=svg)](https://circleci.com/gh/cb-geo/mpmviz)
[![codecov](https://codecov.io/gh/cb-geo/mpmviz/branch/develop/graph/badge.svg)](https://codecov.io/gh/cb-geo/mpmviz)
[![](https://img.shields.io/github/issues-raw/cb-geo/mpmviz.svg)](https://github.com/cb-geo/mpmviz/issues)
[![Project management](https://img.shields.io/badge/projects-view-ff69b4.svg)](https://github.com/cb-geo/mpmviz/projects/)


## Install dependencies

* Docker image for CB-Geo mpmviz code [https://hub.docker.com/r/cbgeo/mpm](https://hub.docker.com/r/cbgeo/mpm)

* Instructions for running mpmviz docker container: [https://github.com/cb-geo/docker-mpm/blob/master/README.md](https://github.com/cb-geo/mpm-container/blob/master/README.md).

### Prerequisite packages
> The following prerequisite packages can be found in the docker image:

* [Boost](http://www.boost.org/)
* [Eigen](http://eigen.tuxfamily.org/)
* [HDF5](https://support.hdfgroup.org/HDF5/)

#### Optional
* [VTK](https://www.vtk.org/)

## Compile
> See https://mpmviz-doc.cb-geo.com/ for more detailed instructions. 

0. Run `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ /path/to/CMakeLists.txt`.

1. Run `make clean && make -jN` (where N is the number of cores).

### Compile mpmviz or mpmviztest

* To compile either `mpmviz` or `mpmviztest` alone, run `make mpmviz -jN` or `make mpmviztest -jN` (where N is the number of cores).

### Compile without tests [Editing CMake options]

To compile without tests run: `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -Dmpmviz_BUILD_TESTING=Off /path/to/CMakeLists.txt`.

### Run tests

0. Run `./mpmviztest -s` (for a verbose output) or `ctest -VV`.
