#!/bin/bash

CURDIR=$(pwd)
cd /
mkdir -p targets
cd targets
mv /Sugarlyzer/resources/programs/varbugs/VarBugsPatches .
cd $CURDIR
