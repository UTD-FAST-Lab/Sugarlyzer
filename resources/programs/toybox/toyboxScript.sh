#!/bin/bash

mkdir -p /targets
CURDIR=$(pwd)
cd /targets
git clone https://github.com/landley/toybox.git
cd toybox/
git checkout 78289203031afc23585035c362beec10db54958dcd busybox-1_28_0
make defconfig
make
echo "" > generated/config.h
cd $CURDIR

