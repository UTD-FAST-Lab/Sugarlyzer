#!/bin/bash

mkdir -p /targets
CURDIR=$(pwd)
cd /targets
apt-get install -y curl
curl -L https://github.com/mirror/busybox/archive/refs/tags/1_28_0.tar.gz --output busybox.tar.gz
tar -xf busybox.tar.gz
cd busybox-1_28_0
make allyesconfig
make
cp /SugarlyzerConfig/busyboxautoconf.h include/autoconf.h
cd $CURDIR

