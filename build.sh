#!/usr/bin/env bash

source ~/.ez80-clang

set -e

echo "Compiling main.c -> main.s"
ez80-clang -isystem ${EZ80_CLANG_SYSTEM_INCLUDE_PATH} -O3 -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S main.c -c -o main.s

echo "Compiling main.s -> main.o"
ez80-as -march=ez80+full -a=./crt.lst ./main.s -o ./main.o
# ez80-clang  -mllvm -z80-print-zero-offset -Wa,-march=ez80 main.c -c -o main.o

echo "Linking libcrt.a main.o -> main.com"
ez80-ld -T linker-script.ld --relax -O1 --strip-discarded --orphan-handling=error --print-map-discarded -Map=main.map -L${EZ80_CLANG_LIB_PATH} -lcrt ./main.o -lclib -lcrt --oformat binary -o main.com

