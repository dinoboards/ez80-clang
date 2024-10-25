
## CLANG based eZ80 compiler

EXPERIMENTAL
WIP

### BASED ON LOTS OF OTHERS WORK:
* https://github.com/codebje/ez80-toolchain
* https://bitbucket.org/cocoacrumbselectronics/minimal-c-runtime/src/master/
* https://bitbucket.org/cocoacrumbselectronics/ez80-llvm-toolchain/src/master/
* https://github.com/jacobly0/llvm-project

....

Docker file to build an image containing a clang compiler that can target the eZ80 CPU.

### Create aliases:

Run the following script to create appropriate shell aliases:

```
./install-alias.sh
```

> Need to source the file ~/.ez80-clang-aliases or open a new terminal

### Example Usage

### Compile Main

```

ez80-as -march=ez80+full -a=./crt.lst ./crt.asm -o ./crt.o

ez80-clang  -mllvm -z80-print-zero-offset -Wa,-march=ez80 main.c -c -o main.o

ez80-objdump -d main.o

# Linking step
ez80-ld -T linker-script.ld -Map=main.map ./crt.o ./main.o --oformat binary -o main.com
```

### Create assembly file

```
ez80-clang  -mllvm -z80-print-zero-offset -S main.c -c -o main.s
```

TODOS
Lib not working???
`ez80-ar rcsv libcrt.a crt0.o` seems to create a lib ok

`ez80-ld -T linker-script.ld -L. -lcrt -Map=main.map  ./main.o --oformat binary -o main.com` is not linking it in
