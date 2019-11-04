FROM ubuntu:18.04

RUN apt-get update \
      && apt-get install -y --no-install-recommends apt-transport-https ca-certificates gnupg software-properties-common wget \
      && add-apt-repository ppa:ubuntu-toolchain-r/test \
      && wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add - \
      && apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main' \
      && apt-get update \
      && apt-get install -y --no-install-recommends \
      build-essential \
      cmake \
      g++-9 \
      git \
      libboost-dev \
      && rm -rf /var/lib/apt/lists/*

ENV CXX=g++-9

RUN git clone --depth 1 --branch v2.10.2 https://github.com/catchorg/Catch2.git \
      && cd Catch2 \
      && cmake -H. -Bbuild -DBUILD_TESTING=OFF \
      && cd build && make install && cd ../.. \
      && rm -rf Catch2

