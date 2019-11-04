# find-critical-path
[![Build Status](https://travis-ci.org/oesse/find-critical-path.svg?branch=master)](https://travis-ci.org/oesse/find-critical-path)

This is a tool to find the critical path in the build process of Yocto
artifacts. It uses the information provided by the task dependency graph and a
build's "buildstats".

### Prerequisites

In order to find the critical path in the build process accurately you need to
run one build with all the targets that you are interested in, e.g. use a clean
build to also consider fetching, or use a build without sstate to consider even
cached steps. In this build you need to enable "buildstats", for example adding
the following to your `local.conf`:
```sh
INHERIT += "buildstats"
```
After the build, make note of your buildstats directory, e.g.
`build/tmp/buildstats/<timestamp>`.

Then, to generate the dependency graph  use bitbake:
```sh
bitbake -g <your-image>
```
This should generate `build/task-depends.dot`.

### Usage

Given that you have the dependency graph and the buildstats directory you can
find the critical path of the build using:
```sh
find-critical-path <path/to/task-depends.dot> <path/to/buildstats-dir>
```

### Build dependencies

In order to build the tool you need
* a C++17 capable compiler and
* [boost](https://www.boost.org/) for
  [Spirit X3](https://www.boost.org/doc/libs/1_71_0/libs/spirit/doc/x3/html/index.html)
  (tested with version 1.71)

Additionally, for development the following things are needed:
* [Catch2](https://github.com/catchorg/Catch2) >= 2.10
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) (optional)

### Build, test, install

Use CMake to build, optionally test and install the tool:
```sh
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make && make test
make install
```

