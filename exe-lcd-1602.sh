#!/bin/bash
cd build
openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program i2c/lcd_1602_i2c/lcd_1602_i2c.elf verify reset exit"
