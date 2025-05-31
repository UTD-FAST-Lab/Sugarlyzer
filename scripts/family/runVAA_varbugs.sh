#!/bin/bash


path=$(pwd)

filesToProcess() {
  local listFile=varbugs/files.txt
  cat $listFile
}

flags=" --bdd --serializeAST \
  -A cfginnonvoidfunction -A doublefree -A xfree -A uninitializedmemory -A casetermination -A danglingswitchcode -A checkstdlibfuncreturn -A deadstore -A interactiondegree \
  -p _\
  -c $path/casestudy/redhat.properties \
  --recordTiming --parserstatistics --lexNoStdout"

filesToProcess|while read i; do
         echo "Analysing $path/varbugs/VarBugsPatches/$i.c"
         echo "With settings: $flags"
         ../TypeChef-VAA/typechef.sh  $path/varbugs/$i $flags
done
