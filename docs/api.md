# eZ80 Clang

The ez80 clang compiler, is a customised version of clang with ez80 support.  It includes support libraries and other facilities to build .COM and .EXE files for the `eZ80 for RC` platform.

### Table of Contents

- Libraries
  - [Memory Models](#memory-models)
  - [Library v99x8](#library-v99x8)
    - [Functions](#v99x8-functions)
    - [Types](#v99x8-types)
  - [Library v99x8-super](#library-v99x8-super)
    - [Functions](#v99x8-super-functions)
  - [Library CP/M](#library-cpm)
    - [Functions](#cpm-functions)
    - [Types](#cpm-types)
  - [Library HBIOS](#library-hbios)
  - [Library eZ80](#library-ez80)
  - [Library eZ80 Firmware](#library-ez80-firmware)

## Memory Models

The compiler can build one of two different binaries for executing on your system.  Both binary types assume the code will be run on a eZ80 CPU with the CP/M operating system running
in the eZ80's compatibility mode.

The type of binary is selected by specifying the required memory model on the `ez80-cc`'s commmand line with the `mem-model` argument.

```
--mem-model type  Specify the memory model: 64KB (default) or 2MB.
```

### COM - 64K Memory

In this mode, the binary must be less than 64K as per a standard `.COM` binary for CP/M.  But unlike standard Z80 .COM binaries, this compiler will include a specific piece of startup code, to switch the CPU to the eZ80's ADL mode -- allowing for full use of the CPU's instruction set.

When your program exits, the code will automatically switch the CPU back to Z80 compatibility mode.

If your program makes any CP/M (or HBIOS) calls, the libraries will ensure the CPU is in Z80 mode whilst executing the CP/M function.

### EXE - 2MB Memory

> This mode requires your ***eZ80 for RC*** have access to a extended linear memory module.

The binary produced, by this mode, will have a .EXE extension and can be larger than 64K.  To execute such a binary, you need to use the `EXE.COM` loader (available within the releases of the [ez80-for-rc](https://github.com/dinoboards/ez80-for-rc/releases) project)

Like the COM version, any calls to CP/M (or HBIOS) will be correctly managed and marhsalled with the CPU's Z80 compatibility mode.

One important point to note for the EXE model, is that any pointers passed to CP/M (or HBIOS) functions must exist within the 64K segement used by CP/M.

You can use the `__attribute((section))` directive to make the c compiler allocate variables
within the required section.

```c
uint8_t buffer[512] __attribute__((section(".bss_z80")));
```


### The available memory sections

The linker configuration used by both memory models provide the following sections:

| Section | 64K .COM Model | 2MB .EXE Model |
| ------------ | --- | --- |
|**.text**         | ADL code | ADL code allocated within extended linear memory, typically starting at $200400 |
|**.rodata**     | read only data | read only data allocated to the extended memory range |
|**.data**    | writable data | writable data allocated to the extended memory range |
|**.bss**   | uninitialised data | uninitialised data allocated to the extended memory range |
|**.bss_z80**   | uninitialised data | uninitialised data allocated within the Z80 compatible segment - typically 0x03xxxx |
|**.text_on_chip**    | for function to be executed from the eZ80 onboard fast RAM | for function to be executed from the eZ80 onboard fast RAM
|**.data_on_chip**    | initialised data copied to the eZ80's onboard fast RAM | initialised data copied to the eZ80's onboard fast RAM |
|**.bss_on_chip**   |uninitialised data allocated within eZ80's onboard fast RAM | uninitialised data allocated within eZ80's onboard fast RAM |

---
