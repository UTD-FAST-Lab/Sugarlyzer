#!/bin/bash


path=$(pwd)

filesToProcess() {
  local listFile=busybox/busybox_files.txt
  cat $listFile
}

flags=" --bdd --serializeAST \
  -A cfginnonvoidfunction -A doublefree -A xfree -A uninitializedmemory -A casetermination -A danglingswitchcode -A checkstdlibfuncreturn -A deadstore -A interactiondegree \
  -p _ \
  -c $path/casestudy/redhat.properties \
  -I $path/busybox/busybox-1_28_0/include \
  --featureModelDimacs $path/busybox/kconfig.dimacs  \
  --recordTiming --parserstatistics --lexNoStdout"

filesToProcess|while read i; do
         echo "Analysing $path/busybox/busybox-1_28_0/$i"
         echo "With settings: $flags"
         ../TypeChef-VAA/typechef.sh  $path/busybox/busybox-1_28_0/$i $flags
done
