#!/bin/bash

cd bin/dotfiles
ffmpeg -framerate 1 -i %04d.dot.png -c:v libx264 -r 30 -pix_fmt yuv420p -s 4038x362 tree.mp4
