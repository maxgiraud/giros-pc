#!/bin/sh

file="`basename \"$1\" gin`bin"
./g2b_compiler/g2b "$1" > "$file"
