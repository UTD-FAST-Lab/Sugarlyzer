#!/bin/bash

mkdir -p /targets
CURDIR=$(pwd)
git clone https://github.com/aJanker/TypeChef-Sampling-OpenSSL.git
git clone https://github.com/aJanker/TypeChef-GNUCHeader.git
cd /targets
cp -r /TypeChef-Sampling-OpenSSL/openssl .
cd $CURDIR
