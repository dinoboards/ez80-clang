#!/usr/bin/env bash

set -e

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

export  DOCKER_BUILDKIT=1

set -x
echo
echo "Building ${EZ80_CLANG_TOOLCHAIN_IMAGE}"
echo
docker build ${EZ80_CLANG_TOOLCHAIN_CACHE_FROM}  --build-arg BUILDKIT_INLINE_CACHE=1 -t ${EZ80_CLANG_TOOLCHAIN_IMAGE} .

echo "Building ${EZ80_CLANG_TOOLCHAIN_BUILDER}"
echo
docker build ${EZ80_CLANG_TOOLCHAIN_CACHE_FROM}  --build-arg BUILDKIT_INLINE_CACHE=1 --target platform -t ${EZ80_CLANG_TOOLCHAIN_PLATFORM} .

echo "Building ${EZ80_CLANG_TOOLCHAIN_BUILDER}"
echo
docker build ${EZ80_CLANG_TOOLCHAIN_CACHE_FROM}  --build-arg BUILDKIT_INLINE_CACHE=1 --target builder -t ${EZ80_CLANG_TOOLCHAIN_BUILDER} .


CLANG_BIN_DIR="opt/ez80-clang/bin"
CLANG_LIB_DIR="opt/ez80-clang/lib/"
CLANG_INCLUDE_DIR="opt/ez80-clang/include/"
CLANG_LS_DIR="opt/ez80-clang/linker-scripts/"
ENV_FILE="ez80-clang"

docker rm -f temp-llvmez80 > /dev/null 2>&1
trap 'docker rm -f temp-llvmez80  > /dev/null 2>&1' EXIT
docker create --name temp-llvmez80 ${EZ80_CLANG_TOOLCHAIN_BUILDER} > /dev/null 2>&1

# ENV vars required
ALIASES=$(cat << 'EOF'
export EZ80_CLANG_SYSTEM_INCLUDE_PATH=/${CLANG_INCLUDE_DIR}
export EZ80_CLANG_LIB_PATH=/${CLANG_LIB_DIR}
export EZ80_CLANG_LS_PATH=/${CLANG_LS_DIR}

if [[ ":\$PATH:" != *":/${CLANG_BIN_DIR}:"* ]]; then
    export PATH="\${PATH}:/${CLANG_BIN_DIR}"
fi

EOF
)

function make_direct_zip() {
  rm -rf tmp/direct
  mkdir -p tmp/direct/ez80-clang-${EZ80_CLANG_TOOLCHAIN_VERSION}
  cd tmp/direct/ez80-clang-${EZ80_CLANG_TOOLCHAIN_VERSION}

  mkdir -p ${CLANG_BIN_DIR}
  mkdir -p ${CLANG_LIB_DIR}
  mkdir -p ${CLANG_INCLUDE_DIR}
  mkdir -p ${CLANG_LS_DIR}

  docker cp "temp-llvmez80:/usr/local/bin/." "${CLANG_BIN_DIR}"
  docker cp "temp-llvmez80:/src/lib/." "${CLANG_LIB_DIR}"
  docker cp "temp-llvmez80:/src/include/." "${CLANG_INCLUDE_DIR}"
  docker cp "temp-llvmez80:/src/linker-scripts/." "${CLANG_LS_DIR}"

  eval "echo \"$ALIASES\"" > "$ENV_FILE"
  cp ../../../install.sh .

  cd ..
  zip -r -0 ../../ez80-clang-${EZ80_CLANG_TOOLCHAIN_VERSION}.zip ez80-clang-${EZ80_CLANG_TOOLCHAIN_VERSION}/*
  tar -czvf ../../ez80-clang-${EZ80_CLANG_TOOLCHAIN_VERSION}.tar.gz ez80-clang-${EZ80_CLANG_TOOLCHAIN_VERSION}/*
}

# tar -xzvf ez80-clang-0.0.5.tar.gz
# cd ez80-clang-0.0.5
# sudo ./install.sh

make_direct_zip
