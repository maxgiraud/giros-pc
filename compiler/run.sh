#!/bin/sh

file="`basename \"$1\" gin`bin"
echo "v2.0 raw" > "$file"
./g2b_compiler/g2b "$1" >> "$file"
