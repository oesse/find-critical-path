#!/bin/sh
set -ex
git clone --depth 1 --branch v2.10.2 https://github.com/catchorg/Catch2.git
cd Catch2 \
  && cmake -H. -Bbuild -DBUILD_TESTING=OFF \
  && cd build && sudo make install
