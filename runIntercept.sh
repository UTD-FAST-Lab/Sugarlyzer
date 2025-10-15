#!/bin/sh

EXTRACTED_LIST="${EXTRACTED_LIST:-extracted_files.txt}"

for arg in "$@"; do
  case "$arg" in
    *.c|*.h)
      if [ -f "$arg" ]; then
        if [ "${arg#/}" != "$arg" ]; then
          fullpath="$arg"
        else
          fullpath="$(cd "$(dirname "$arg")" 2>/dev/null && pwd)/$(basename "$arg")"
        fi

        # Check if this path is already in the file to avoid duplicates
        if ! grep -Fxq "$fullpath" "$EXTRACTED_LIST" 2>/dev/null; then
            printf "%s\n" "$fullpath" >> "$EXTRACTED_LIST"
        fi
      fi
      ;;
  esac
done


# Check if file was created and show its contents
if [ "$SUGARLYZER_DEBUG" = "true" ]; then

  if [ -f "$EXTRACTED_LIST" ]; then
    echo "DEBUG: File $EXTRACTED_LIST exists, size: $(wc -c < "$EXTRACTED_LIST") bytes" >&2
    echo "DEBUG: Contents:" >&2
    cat "$EXTRACTED_LIST" >&2
  else
    echo "DEBUG: File $EXTRACTED_LIST was NOT created" >&2
  fi

fi


exec gcc "$@"
