#!/usr/bin/env bash

source ~/.ez80-clang

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

export EZ80_CLANG_SYSTEM_INCLUDE_PATH=${SCRIPT_DIR}/include
export EZ80_CLANG_LIB_PATH=${SCRIPT_DIR}/lib/
export EZ80_CLANG_LS_PATH=${SCRIPT_DIR}/linker-scripts/

export INCLUDE_PATHS="-isystem ${SCRIPT_DIR}/include -isystem ${SCRIPT_DIR}/working/llvm-project/build/lib/clang/15.0.0/include/"
PATH="${SCRIPT_DIR}working/llvm-project/build/bin:${SCRIPT_DIR}working/opt/ez80-none-elf/bin/:${PATH}"

shopt -s expand_aliases
alias ez80-clang="clang -nostdinc"
alias ez80-as="ez80-none-elf-as"
alias ez80-ld="ez80-none-elf-ld"


set -e

echo "Compiling main.c -> main.s"
ez80-clang ${INCLUDE_PATHS} -nostdinc -ffunction-sections -fdata-sections -Oz -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S main.c -c -o main.s

echo "Compiling nanoprintf.c -> nanoprintf.s"
ez80-clang ${INCLUDE_PATHS} -nostdinc -ffunction-sections -fdata-sections -Oz -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S nanoprintf.c -c -o nanoprintf.s

echo "Compiling nanoprintf.s -> nanoprintf.o"
ez80-as -march=ez80+full -a=./nanoprintf.lst ./nanoprintf.s -o ./nanoprintf.o

echo "Compiling main.s -> main.o"
ez80-as -march=ez80+full -a=./main.lst ./main.s -o ./main.o

echo "Linking libcrt.a main.o -> main.com"
ez80-ld -T linker-script.ld --relax -O1  --gc-sections --strip-discarded --orphan-handling=error --print-map-discarded -Map=main.map -L${EZ80_CLANG_LIB_PATH} -lcrt ./main.o  -llibc -lcrt --oformat binary -o main.com

