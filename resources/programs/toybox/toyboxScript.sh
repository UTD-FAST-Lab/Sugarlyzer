#!/bin/bash

export PROGRAM="toybox"

mkdir -p /targets
CURDIR=$(pwd)
cd /targets
git clone https://github.com/landley/toybox.git
cd toybox/
git checkout 78289203031afc23585035c362beec10db54958d
make defconfig

make CC="/Sugarlyzer/resources/tools/$TOOL/run$TOOL.sh"

cp /SugarlyzerConfig/toyboxConfig.h generated/config.h
cd $CURDIR

