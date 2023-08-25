#!/bin/bash
openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program HCSR04/HCSR04.elf verify reset exit"
