#!/bin/bash
cd build
openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program test-read-crc16/test-read-crc16.elf  verify reset exit"
