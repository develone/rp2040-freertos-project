#!/bin/bash
rm -rf build 
mkdir build
cd build/
cmake -DPICO_BOARD=pico2 -DFREERTOS_KERNEL_PATH:PATH=../freertos/FreeRTOS-Kernel/ ..
make

