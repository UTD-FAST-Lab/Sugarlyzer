#!/bin/bash

mkdir -p /targets
CURDIR=$(pwd)
git clone https://github.com/aJanker/TypeChef-Sampling-Linux.git
git clone https://github.com/aJanker/TypeChef-GNUCHeader.git
git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/stable/linux-stable
cd /linux-stable
git checkout af352dbf0b0a8d9d4c17018d63fae48b654fd03b
cd $CURDIR
cd /targets
cp -r /linux-stable linux
cd linux
make allnoconfig ARCH=x86
make prepare ARCH=x86
make SUBDIRS=init ARCH=x86 &> /dev/null
cd $CURDIR
