
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
wget http://www.dinoboards.com.au/ez80-clang/ez80-clang-0.0.11.tar.gz
tar -xzvf ez80-clang-0.0.11.tar.gz
cd ez80-clang-0.0.11
sudo ./install.sh
```

> Change version as per current release

It will be installed into `/opt/ez80-clang/...`

It will also add the file `~/.ez80-clang` containing  required environment variables.

Your `~/.bashrc` file will be updated to source this file.

## Building an CP/M eZ80 Application

Once installed, you can use the `ez80-cc` wrapper command to compile, assemble and link an application

eg:

```
ez80-cc HELOWRLD.COM hello-world.c
```

## Building

```
make package
```

## Installing from local build

```
sudo make install
```


## C Runtime Status

[List of ported/implemented c runtime function](./runtime-implementation-status.md)
