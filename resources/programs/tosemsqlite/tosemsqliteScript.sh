#!/bin/bash

mkdir -p /targets
CURDIR=$(pwd)
git clone https://github.com/aJanker/TypeChef-Sampling-SQLite.git
git clone https://github.com/aJanker/TypeChef-GNUCHeader.git
cd /targets
cp -r /TypeChef-Sampling-SQLite/sqlite .
cd $CURDIR
