#!/bin/bash

arduino-cli upload --profile xiao_rp2040 -p /dev/ttyACM0 --input-file ./build/dot_canvas_simple.ino.uf2
#arduino-cli upload --profile xiao_rp2350 -p /dev/ttyACM0 --input-file ./build/dot_canvas_simple.ino.uf2
