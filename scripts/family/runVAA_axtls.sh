#!/bin/bash

path=$(pwd)

TYPECHEF_PATH="${1:-.}"
OUTPUT_DIR="${2:-.}"

AXTLS_PATH=$(find "$path" -type d -name "axtls-code" -print -quit)
CASESTUDY_PATH=$(find "$path" -type d -name "casestudy" -print -quit)
SOUSCHEF_PATH=$(find "$path" -type f -name "souschef.sh" -print -quit)

cd $(dirname "$AXTLS_PATH") || exit 1

filesToProcess() {
  local listFile=axtls_files.txt
  cat $listFile
}

flags=" --bdd --serializeAST \
  -A cfginnonvoidfunction -A doublefree -A xfree -A uninitializedmemory -A casetermination -A danglingswitchcode -A checkstdlibfuncreturn -A deadstore -A interactiondegree \
  -p _\
  --errorXML=$OUTPUT_DIR/axtls_errors.xml \
  -c $CASESTUDY_PATH/redhat.properties \
  -I $CASESTUDY_PATH/systems/redhat/usr/include \
  -I $CASESTUDY_PATH/systems/redhat/usr/lib/gcc/x86_64-redhat-linux/4.4.4/include \
  -I $AXTLS_PATH/config \
  -I $AXTLS_PATH/crypto \
  -I $AXTLS_PATH/ssl \
  -I $AXTLS_PATH/httpd \
  --featureModelDimacs kconfig.dimacs  \
  --recordTiming --parserstatistics --lexNoStdout"

filesToProcess|while read file; do
  echo "Analysing $AXTLS_PATH/$file"
  echo "With settings: $flags"
  "$TYPECHEF_PATH/typechef.sh" "axtls-code/$file" $flags > "$OUTPUT_DIR/$(basename "$file").log" 2>&1
done

if [[ -f "$SOUSCHEF_PATH" ]]; then
  echo "Aggregating results to $OUTPUT_DIR/results.json..."
  cat "$OUTPUT_DIR"/*.log | python3 "$SOUSCHEF_PATH" > "$OUTPUT_DIR/results.json"
else
  echo "Warning: souschef.sh not found. Skipping JSON aggregation"
fi
