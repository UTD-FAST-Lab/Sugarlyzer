#!/bin/bash

mkdir -p /targets
CURDIR=$(pwd)
cd /targets
apt-get install -y curl
curl -L https://sourceforge.net/projects/axtls/files/2.1.4/axTLS-2.1.4.tar.gz/download --output axtls.tar.gz
tar -xf axtls.tar.gz
cd axtls-code
make linuxconf
cd $CURDIR

