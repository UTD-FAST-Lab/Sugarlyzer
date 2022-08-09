#!/bin/bash

CURDIR=$(pwd)
cd /
mkdir -p targets
cd targets
git clone https://github.com/pattersonz/VarBugsPatches
cd $CURDIR