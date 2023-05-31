#!/bin/bash
cd build
openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program i2c/slave_i2c/slave_i2c.elf verify reset exit"
