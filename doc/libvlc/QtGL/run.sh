#!/bin/bash -e

qmake
make -j
make clean
./qtglvlc file://$HOME/Vidéos/fancier-plasma.mp4
