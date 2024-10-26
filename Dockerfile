# from within the programmer dir
#
# docker build --progress plain -t dinoboards/llvmez80:0.0.3 .
#
# docker run -v ${PWD}:/src/ -u $(id -u ${USER}):$(id -g ${USER}) -it dinoboards/llvmez80:0.0.3


FROM ubuntu:focal-20240530 AS platform

ENV DEBIAN_FRONTEND=noninteractive

RUN sed -i 's/http:\/\/archive\.ubuntu\.com\/ubuntu/http:\/\/mirror.internode.on.net\/pub\/ubuntu\/ubuntu/g'  /etc/apt/sources.list
RUN sed -i 's/http:\/\/security\.ubuntu\.com\/ubuntu/http:\/\/mirror.internode.on.net\/pub\/ubuntu\/ubuntu/g'  /etc/apt/sources.list

RUN rm -rfv /var/lib/apt/lists/* && \
    apt clean && \
    apt update && \
    apt dist-upgrade -y && \
    apt install -y \
    build-essential \
    curl \
    git \
    python3 \
    software-properties-common \
    wget

LABEL Maintainer="Dean Netherton" \
      Description="tool chain for llvm-project (ez80)"

RUN apt install cmake ninja-build -y
WORKDIR /src
RUN adduser --disabled-password --gecos "" builder

FROM platform AS builder

RUN git clone --depth 1 --branch ez80-for-rc-clang-tool-chain https://github.com/dinoboards/llvm-project.git

WORKDIR /src/llvm-project
# ARG COMMIT_SHA=365875982bd3e1ee0d572d4d8d34cb45870ee742
RUN git fetch --depth 1 origin 610487e5a2606567dc472eab6af41c09d7412837
# $COMMIT_SHA
RUN git checkout 610487e5a2606567dc472eab6af41c09d7412837

RUN cmake -S llvm -B build -G Ninja \
    -DLLVM_ENABLE_PROJECTS="clang" \
    -DCMAKE_INSTALL_PREFIX=/opt/local/z80-none-elf \
    -DBOOTSTRAP_CMAKE_BUILD_TYPE=Release \
    -DCLANG_ENABLE_BOOTSTRAP=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=Z80 \
    -DLLVM_TARGETS_TO_BUILD="" \
    -DLLVM_DEFAULT_TARGET_TRIPLE=ez80-none-elf

RUN cmake --build build

# RUN ls -lartsh /src/llvm-project/build/lib/clang/15.0.0/include
# What about version 2.43???

WORKDIR /src
ADD https://ftp.gnu.org/gnu/binutils/binutils-2.37.tar.gz ./binutils-2.37.tar.gz
RUN tar xf binutils-2.37.tar.gz
WORKDIR /src/binutils-2.37
RUN ./configure --target=z80-none-elf --program-prefix=ez80-none-elf- --prefix=/opt/ez80-none-elf
RUN make -j
RUN make install

FROM ubuntu:focal-20240530

RUN adduser --disabled-password --gecos "" builder

WORKDIR /src
COPY --from=builder /opt/ez80-none-elf/bin /usr/local/bin/
COPY --from=builder /src/llvm-project/build/bin /usr/local/bin/

# ENV C_INCLUDE_PATH=/usr/local/lib/clang/15.0.0


# compiling: clang -target ez80-none-elf -mllvm -z80-print-zero-offset -Wa,-march=ez80, -nostdinc main.c -c -o main.o
# ez80-none-elf-objdump -d main.o
