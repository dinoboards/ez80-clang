FROM ubuntu:focal-20240530 AS platform

ENV DEBIAN_FRONTEND=noninteractive

RUN rm -rfv /var/lib/apt/lists/*
RUN apt clean
RUN apt update
RUN apt upgrade -y
RUN apt install -y build-essential
RUN apt install -y curl
RUN apt install -y git
RUN apt install -y python3
RUN apt install -y software-properties-common
RUN apt install -y wget

LABEL Maintainer="Dean Netherton" \
      Description="tool chain for llvm-project (ez80)"

RUN apt install cmake ninja-build -y
WORKDIR /src
RUN adduser --disabled-password --gecos "" builder

FROM platform AS builder

RUN git clone --depth 1 --branch ez80-for-rc-clang-tool-chain https://github.com/dinoboards/llvm-project.git

WORKDIR /src/llvm-project
# ARG COMMIT_SHA=365875982bd3e1ee0d572d4d8d34cb45870ee742
RUN git fetch --depth 1 origin da4c66ccd1e01a212c4f07af91749e16a12f6423
# $COMMIT_SHA
RUN git checkout da4c66ccd1e01a212c4f07af91749e16a12f6423

RUN cmake -S llvm -B build -G Ninja \
    -DLLVM_ENABLE_PROJECTS="clang" \
    -DCMAKE_INSTALL_PREFIX=/opt/local/z80-none-elf \
    -DBOOTSTRAP_CMAKE_BUILD_TYPE=Release \
    -DCLANG_ENABLE_BOOTSTRAP=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=Z80 \
    -DLLVM_TARGETS_TO_BUILD="" \
    -DLLVM_DEFAULT_TARGET_TRIPLE=ez80-none-elf

RUN BUILD_THREADS=$(nproc) && BUILD_THREADS=$((BUILD_THREADS * 7 / 10)) && [ "$BUILD_THREADS" -lt 4 ] && BUILD_THREADS=1 || true && cmake --build build -j $BUILD_THREADS

# apply 2nd patch
RUN git fetch --depth 1 origin 85d408fe6bc12f624f4990e20dea30d1c3dd59e3
RUN git checkout 85d408fe6bc12f624f4990e20dea30d1c3dd59e3
RUN cmake -S llvm -B build -G Ninja \
    -DLLVM_ENABLE_PROJECTS="clang" \
    -DCMAKE_INSTALL_PREFIX=/opt/local/z80-none-elf \
    -DBOOTSTRAP_CMAKE_BUILD_TYPE=Release \
    -DCLANG_ENABLE_BOOTSTRAP=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=Z80 \
    -DLLVM_TARGETS_TO_BUILD="" \
    -DLLVM_DEFAULT_TARGET_TRIPLE=ez80-none-elf
RUN BUILD_THREADS=$(nproc) && BUILD_THREADS=$((BUILD_THREADS * 7 / 10)) && [ "$BUILD_THREADS" -lt 4 ] && BUILD_THREADS=1 || true && cmake --build build -j $BUILD_THREADS


WORKDIR /src
ADD https://ftp.gnu.org/gnu/binutils/binutils-2.43.tar.gz ./binutils-2.43.tar.gz
RUN tar xf binutils-2.43.tar.gz
WORKDIR /src/binutils-2.43
RUN ./configure --target=z80-none-elf --program-prefix=ez80-none-elf- --prefix=/opt/ez80-none-elf
RUN make -j
RUN make install

RUN mkdir -p /opt/ez80-clang/bin
RUN cp /opt/ez80-none-elf/bin/* /opt/ez80-clang/bin/
RUN ln -s ez80-none-elf-ar /opt/ez80-clang/bin/ez80-ar
RUN ln -s ez80-none-elf-as /opt/ez80-clang/bin/ez80-as
RUN cp /src/llvm-project/build/bin/clang-15 /opt/ez80-clang/bin/ez80-clang-15
RUN cp /src/llvm-project/build/bin/clang-format /opt/ez80-clang/bin/ez80-clang-format

RUN mkdir -p /src/include
RUN cp /src/llvm-project/build/lib/clang/15.0.0/include/stdbool.h /src/include/stdbool.h
RUN cp /src/llvm-project/build/lib/clang/15.0.0/include/stdint.h /src/include/stdint.h
RUN cp /src/llvm-project/build/lib/clang/15.0.0/include/stddef.h /src/include/stddef.h
RUN cp /src/llvm-project/build/lib/clang/15.0.0/include/__stddef_max_align_t.h /src/include/__stddef_max_align_t.h
RUN cp /src/llvm-project/build/lib/clang/15.0.0/include/stdarg.h /src/include/stdarg.h

