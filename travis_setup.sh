#!/bin/bash

mkdir cbuild
mkdir cbuild/install

wget https://github.com/protocolbuffers/protobuf/releases/download/v3.12.3/protobuf-cpp-3.12.3.tar.gz
tar xvf protobuf-cpp-3.12.3.tar.gz -C ./cbuild --strip-components=1

if [[ "$TRAVIS_OS_NAME" == "osx" || "$TRAVIS_OS_NAME" == "linux" ]]; then
  cd cbuild
  ./configure --prefix=$(pwd)/install "CFLAGS=-fPIC" "CXXFLAGS=-fPIC"
  make
  make install
  cd ..
  pwd
  ls
  ls cbuild
  ls cbuild/install
elif [[ "$TRAVIS_OS_NAME" == "windows" ]]; then
  mkdir cbuild/cmake/solution
  cd cbuild/cmake/solution
  cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=../../install ..
  cmake --build . --config Release
  cmake --build . --config Release --target install
  cd ../../..
  pwd
  ls
  ls cbuild
  ls cbuild/install  
else
  echo "$TRAVIS_OS_NAME is currently not supported"  
fi
