#!/bin/bash
rm -rf build-2040 
mkdir build-2040
cd build-2040
cmake -DPICO_BOARD=pico ..
make

