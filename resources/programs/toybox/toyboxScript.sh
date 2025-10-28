#!/bin/bash

echo "Setting PROGRAM to toybox" >&2
export PROGRAM="toybox"

mkdir -p /targets
CURDIR=$(pwd)
cd /targets
git clone https://github.com/landley/toybox.git
cd toybox/
git checkout 78289203031afc23585035c362beec10db54958d
make defconfig
make
cp /SugarlyzerConfig/toyboxConfig.h generated/config.h
cd $CURDIR

