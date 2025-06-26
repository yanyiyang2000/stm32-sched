#!/bin/bash

BUILD_TYPE=Debug

if [ ! -d "build" ]; then
    cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE -B build .
fi

cmake --build ./build
