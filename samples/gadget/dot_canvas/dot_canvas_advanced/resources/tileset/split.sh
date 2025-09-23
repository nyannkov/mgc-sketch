#!/bin/bash

SPLIT_PY=../../../../../../libs/mgc/tools/anim_frame_splitter/anim_frame_splitter.py

python3 $SPLIT_PY ./tileset_chick.bmp --width 6 --height 10 --dir ../anim/anim_chick/
python3 $SPLIT_PY ./tileset_hen.bmp --width 6 --height 10 --dir ../anim/anim_hen/
