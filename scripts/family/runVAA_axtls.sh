#!/bin/bash


path=$(pwd)

filesToProcess() {
  local listFile=axtls/axtls_files.txt
  cat $listFile
}

flags=" --bdd --serializeAST \
  -A cfginnonvoidfunction -A doublefree -A xfree -A uninitializedmemory -A casetermination -A danglingswitchcode -A checkstdlibfuncreturn -A deadstore -A interactiondegree \
  -p _\
  --errorXML=./axtls_errors.xml \
  -c $path/casestudy/redhat.properties \
  -I $path/axtls/axtls-code/config \
  -I $path/axtls/axtls-code/crypto \
  -I $path/axtls/axtls-code/ssl \
  -I $path/axtls/axtls-code/httpd \
  --featureModelDimacs $path/axtls/kconfig.dimacs  \
  --recordTiming --parserstatistics --lexNoStdout"

filesToProcess|while read i; do
         echo "Analysing $path/axtls/axtls-code/$i.c"
         echo "With settings: $flags"
         ../TypeChef-VAA/typechef.sh  $path/axtls/axtls-code/$i $flags
done
