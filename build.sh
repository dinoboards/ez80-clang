#!/usr/bin/env bash

source ~/.ez80-clang-aliases

set -e

pushd ./
make
# pwd
# alias | grep ez80-as
# echo "Assembling crt0.asm -> crt0.o"
# ez80-as -march=ez80+full -a=./crt.lst ./crt0.asm -o ./crt0.o

# echo "Adding crt0.o to libcrt.a"
# ez80-ar rcs ../lib/libcrt.a crt0.o

popd

# echo "Compiling nanoprintf.c -> nanoprintf.s"
# ez80-clang -nostdinc -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S nanoprintf.c -c -o nanoprintf.s

# echo "Compiling nanoprintf.s -> nanoprintf.o"
# ez80-as -march=ez80+full -a=./crt.lst ./nanoprintf.s -o ./nanoprintf.o

# echo "Adding nanoprintf.o to libnanoprintf.a"
# ez80-ar rcs libnanoprintf.a nanoprintf.o

echo "Compiling main.c -> main.s"
ez80-clang -nostdinc -O3 -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S main.c -c -o main.s

echo "Compiling main.s -> main.o"
ez80-as -march=ez80+full -a=./crt.lst ./main.s -o ./main.o
# ez80-clang  -mllvm -z80-print-zero-offset -Wa,-march=ez80 main.c -c -o main.o

echo "Linking libcrt.a main.o -> main.com"
ez80-ld -T linker-script.ld --relax -V -O1 --strip-discarded --orphan-handling=error -t --print-map-discarded -Map=main.map -L./lib/ -lcrt ./main.o -lclib -lcrt --oformat binary -o main.com

# # z80-ld -T linker-script.ld --orphan-handling=error -t -t --print-map-discarded -print-map -Map=main.map ./crt0.o ./main.o --oformat binary -o main.com


# export C_INCLUDE_PATH=/src/working/llvm-project/build/lib/clang/15.0.0/include/:/src/includes/
# /src/working/llvm-project/build/bin/clang -nostdinc -Wall -Wextra -Wunreachable-code -Werror -isystem "./includes" -mllvm -z80-print-zero-offset -S main.c -c -o main.s
# /src/working/opt/ez80-none-elf/bin/ez80-none-elf-as -march=ez80+full -a=./crt.lst ./main.s -o ./main.o
