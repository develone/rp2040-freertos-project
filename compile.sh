#!/bin/bash
rm -rf build 
mkdir build
cd build/
cmake -DPICO_BOARD=pico ..
make

