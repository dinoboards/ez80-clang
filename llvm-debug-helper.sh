#!/usr/bin/env bash

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

LOCAL_OPT="/host${SCRIPT_DIR}/working/opt/"

source ~/.ez80-clang
source version.sh

export EZ80_CLANG_TOOLCHAIN_PLATFORM="dinoboards/llvmez80-platform:${EZ80_CLANG_TOOLCHAIN_VERSION}"

set -e


# docker build --target platform -t ${EZ80_CLANG_TOOLCHAIN_PLATFORM} .

pushd working/llvm-project

# export CLANG_DOCKER_OPTIONS="-v ${EZ80_CLANG_LIB_PATH}:${SCRIPT_DIR}/lib -v ${EZ80_CLANG_LS_PATH}:${SCRIPT_DIR}/linker-scripts -v ${EZ80_CLANG_SYSTEM_INCLUDE_PATH}:${SCRIPT_DIR}/include -w /host/${PWD} -v /:/host/ -u $(id -u ${USER}):$(id -g ${USER})"
export CLANG_DOCKER_OPTIONS="-w /host/${PWD} -v /:/host/ -u $(id -u ${USER}):$(id -g ${USER})"

# docker run ${CLANG_DOCKER_OPTIONS} -t ${EZ80_CLANG_TOOLCHAIN_PLATFORM} cmake -S llvm -B build -G Ninja \
#     -DLLVM_ENABLE_PROJECTS="clang" \
#     -DCMAKE_INSTALL_PREFIX=${LOCAL_OPT}/z80-none-elf \
#     -DBOOTSTRAP_CMAKE_BUILD_TYPE=Release \
#     -DCLANG_ENABLE_BOOTSTRAP=ON \
#     -DCMAKE_BUILD_TYPE=Release \
#     -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=Z80 \
#     -DLLVM_TARGETS_TO_BUILD="" \
#     -DLLVM_DEFAULT_TARGET_TRIPLE=ez80-none-elf

docker run ${CLANG_DOCKER_OPTIONS} -t ${EZ80_CLANG_TOOLCHAIN_PLATFORM} cmake --build build -j 24

popd

pushd working/binutils-2.37
export CLANG_DOCKER_OPTIONS="-w /host/${PWD} -v /:/host/ -u $(id -u ${USER}):$(id -g ${USER})"

docker run ${CLANG_DOCKER_OPTIONS} -t ${EZ80_CLANG_TOOLCHAIN_PLATFORM} ./configure --target=z80-none-elf --program-prefix=ez80-none-elf- --prefix=${LOCAL_OPT}/ez80-none-elf
docker run ${CLANG_DOCKER_OPTIONS} -t ${EZ80_CLANG_TOOLCHAIN_PLATFORM} make -j 24

echo "---------------"
echo docker run ${CLANG_DOCKER_OPTIONS} -t ${EZ80_CLANG_TOOLCHAIN_PLATFORM} make install

popd
