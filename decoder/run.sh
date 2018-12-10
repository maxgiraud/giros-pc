#!/bin/sh

echo "v2.0 raw" > decoder_rom.dat
./decrom_gen >> decoder_rom.dat
