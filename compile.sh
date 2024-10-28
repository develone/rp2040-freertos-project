#!/bin/bash
rm -rf build 
mkdir build
cd build/
cmake -DPICO_BOARD=pico -DFREERTOS_KERNEL_PATH=../freertos/FreeRTOS-Kernel ..
make

