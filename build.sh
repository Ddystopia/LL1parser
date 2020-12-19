#!/bin/sh

mkdir -p build
cd ./build
if [ ! -f "./CMakeCache.txt" ]; then
  cmake -G "CodeLite - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
fi
make
cd ..
