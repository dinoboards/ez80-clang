
## Clang compiler for eZ80

VERY MUCH A WORK IN PROGRESS

### BASED ON LOTS OF OTHERS WORK:
* https://bitbucket.org/cocoacrumbselectronics/ez80-llvm-toolchain/src/master/
* https://bitbucket.org/cocoacrumbselectronics/minimal-c-runtime/src/master/
* https://github.com/codebje/ez80-toolchain
* https://github.com/jacobly0/llvm-project
* https://github.com/pcawte/AgDev

....

## Clang for eZ80 on the RC platform

A cross clang-compiler tool chain.  Generating ADL eZ80 code, with a runtime to marshal the standard c runtime functions through CP/M.

The generated code from the compiler assumes (at this stage):

* That its going to be loaded within a standard CP/M environment - loading at address $0100
* That the code will be started in Z80 mode, with MBASE currently set to $03.  That is, the code will actually be loaded at $030100

The compiler has been built for a Debian/ubuntu environment - other linux environments may or may not work.

## Installing

A build for ubuntu/debian can be installed from github's releases.

To install:

```
wget https://github.com/dinoboards/ez80-clang/releases/download/v0.0.13-rc.116/ez80-clang-v0.0.13-rc.116.tar.gz
tar -xzvf ez80-clang-v0.0.13-rc.116.tar.gz
cd ez80-clang-v0.0.13-rc.116
sudo ./install.sh
```

> Change version as per current release

It will be installed into `/opt/ez80-clang/...`

It will also add the file `~/.ez80-clang` containing  required environment variables.

Your `~/.bashrc` file will be updated to source this file.

## Building a CP/M eZ80 Application

Once installed, you can use the `ez80-cc` wrapper command to compile, assemble and link an application.

eg:

```
ez80-cc HELOWRLD.COM hello-world.c
```

## ez80-cc

```
Usage: ez80-cc [--output-dir dir] [--iquote dir] [--optimise type] [output] source-files...
Options:
  --output-dir dir  Specify the output directory for the binary file.
  --iquote dir      Specify an additional include directory for the compiler.
  --optimise type   Specify the optimisation type (size or speed).
  --lib type        Specify the library: v99x8-standard(default) or v99x8-hdmi.
  --mem-model type  Specify the memory model: 64KB (default) or 2MB.
  --help            Display this help message.

Arguments:
  output            The name of the output .com file. If not supplied,
                    the name is inferred from the name of the first source-file.
  source-files      The input files to be compiled or assembled. Must be
                    .asm or .c files

* 2MB files should have extension of .EXE to indicate non standard CP/M application.
```

For loading and executing EXE files, see within the `ez80-for-RC` github repo, the `EXE.COM` application: [https://github.com/dinoboards/ez80-for-rc/tree/main/apps/exe](https://github.com/dinoboards/ez80-for-rc/tree/main/apps/exe)

You can also find many example applications implemented in that project also: [https://github.com/dinoboards/ez80-for-rc/tree/main/apps](https://github.com/dinoboards/ez80-for-rc/tree/main/apps)


## Libraries/API reference

Most of the standard c libraries (crt, libc, file io, malloc, etc) are implemented.  There are also libraries included specific to the eZ80 and associated hardware.

See the seperate document for references: [Library API](./library-apis.md)

---

## Building the Tool chain

```
make package-local
```

## Installing from local build

```
sudo make install
```

