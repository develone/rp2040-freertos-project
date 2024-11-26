#!/bin/bash
rm -rf build 
mkdir build-2350
cd build-2350
cmake -DPICO_BOARD=pico2 ..
make

