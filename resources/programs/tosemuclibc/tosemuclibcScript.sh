#!/bin/bash

mkdir -p /targets
CURDIR=$(pwd)
git clone https://github.com/aJanker/TypeChef-Sampling-uClibc.git
git clone https://github.com/aJanker/TypeChef-GNUCHeader.git
echo "_LIBC" >> /TypeChef-GNUCHeader/platform.h
cd /targets
cp -r /TypeChef-Sampling-uClibc/study/farce-uclibc/uClibc .
cd $CURDIR
