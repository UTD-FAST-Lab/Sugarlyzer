#!/bin/bash

export PROGRAM="axtls"

mkdir -p /targets
CURDIR=$(pwd)
cd /targets
apt-get update -y && apt-get install -y curl
curl -L https://sourceforge.net/projects/axtls/files/2.1.4/axTLS-2.1.4.tar.gz/download --output axtls.tar.gz
tar -xf axtls.tar.gz
cd axtls-code

make linuxconf CC="/Sugarlyzer/resources/tools/$TOOL/run$TOOL.sh"

cp /SugarlyzerConfig/axtlsconfig.h config/config.h
cd $CURDIR

