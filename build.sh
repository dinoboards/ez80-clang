#!/usr/bin/env bash

source ~/.ez80-clang-aliases

shopt -s expand_aliases

echo "Assembling crt0.asm -> crt0.o"
ez80-as -march=ez80+full -a=./crt.lst ./crt0.asm -o ./crt0.o

echo "Compiling main.c -> main.o"
ez80-clang  -mllvm -z80-print-zero-offset -Wa,-march=ez80 main.c -c -o main.o

echo "Linking crt0.o main.o -> main.com"
ez80-ld -T linker-script.ld --orphan-handling=error -t -t --print-map-discarded -print-map -Map=main.map ./crt0.o ./main.o --oformat binary -o main.com
