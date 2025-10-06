#!/bin/bash


path=$(pwd)

filesToProcess() {
  local listFile=casestudy/busybox_files
  cat $listFile
}

flags=" --bdd --serializeAST \
  -A cfginnonvoidfunction -A doublefree -A xfree -A uninitializedmemory -A casetermination -A danglingswitchcode -A checkstdlibfuncreturn -A deadstore -A interactiondegree \
  -x CONFIG_ \
  -c $path/casestudy/redhat.properties \
  --include $path/casestudy/config.h \
  -I $path/busybox-1.18.5/include \
  --featureModelDimacs $path/casestudy/BB_fm.dimacs  \
  --recordTiming --parserstatistics --lexNoStdout \
  -U HAVE_LIBDMALLOC \
  -DCONFIG_FIND \
  -U CONFIG_FEATURE_WGET_LONG_OPTIONS \
  -U ENABLE_NC_110_COMPAT \
  -U CONFIG_EXTRA_COMPAT \
  -D_GNU_SOURCE"

filesToProcess|while read i; do
         echo "Analysing $path/busybox-1.18.5/$i.c"
         echo "With settings: $flags"
         ../TypeChef-VAA/typechef.sh  $path/busybox-1.18.5/$i.c $flags
done
