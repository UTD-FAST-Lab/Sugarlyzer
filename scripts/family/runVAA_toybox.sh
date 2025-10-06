#!/bin/bash


path=$(pwd)

filesToProcess() {
  local listFile=toybox/toybox_files.txt
  cat $listFile
}

flags=" --bdd --serializeAST \
  -A cfginnonvoidfunction -A doublefree -A xfree -A uninitializedmemory -A casetermination -A danglingswitchcode -A checkstdlibfuncreturn -A deadstore -A interactiondegree \
  -p _ \
  -c $path/casestudy/redhat.properties \
  -I $path/toybox/toybox \
  --featureModelDimacs $path/toybox/kconfig.dimacs  \
  --recordTiming --parserstatistics --lexNoStdout"

filesToProcess|while read i; do
         echo "Analysing $path/toybox/toybox/$i.c"
         echo "With settings: $flags"
         ../TypeChef-VAA/typechef.sh  $path/toybox/toybox/$i $flags
done
