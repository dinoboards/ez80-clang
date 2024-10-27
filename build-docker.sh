#!/usr/bin/env bash

set -e

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

export BUILD_THREADS=$(nproc) && BUILD_THREADS=$((BUILD_THREADS * 8 / 10)) && [ "$BUILD_THREADS" -lt 1 ] && BUILD_THREADS=1 || true


echo "Building ${EZ80_CLANG_TOOLCHAIN_BUILDER}"
echo
docker build --build-arg BUILD_THREADS=${BUILD_THREADS} --target builder -t ${EZ80_CLANG_TOOLCHAIN_BUILDER} .

echo
echo "Building ${EZ80_CLANG_TOOLCHAIN_IMAGE}"
echo
docker build --build-arg BUILD_THREADS=${BUILD_THREADS} -t ${EZ80_CLANG_TOOLCHAIN_IMAGE} .


CLANG_BIN_DIR="opt/clang-for-rc/bin/"
CLANG_LIB_DIR="opt/clang-for-rc/lib/"
CLANG_INCLUDE_DIR="opt/clang-for-rc/include/"
CLANG_LS_DIR="opt/clang-for-rc/linker-scripts/"
ENV_FILE="opt/clang-for-rc/ez80-clang"

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
  mkdir -p tmp/direct
  cd tmp/direct

  mkdir -p ${CLANG_BIN_DIR}
  mkdir -p ${CLANG_LIB_DIR}
  mkdir -p ${CLANG_INCLUDE_DIR}
  mkdir -p ${CLANG_LS_DIR}

  docker cp "temp-llvmez80:/usr/local/bin/." "${CLANG_BIN_DIR}"
  docker cp "temp-llvmez80:/src/lib/." "${CLANG_LIB_DIR}"
  docker cp "temp-llvmez80:/src/include/." "${CLANG_INCLUDE_DIR}"
  docker cp "temp-llvmez80:/src/linker-scripts/." "${CLANG_LS_DIR}"

  eval "echo \"$ALIASES\"" > "$ENV_FILE"

  cd opt/clang-for-rc
  zip -r -0 ../../../ez80-clang-direct.zip ./*
}

function main_docker_zip() {
  rm -rf tmp/docker
  mkdir -p tmp/docker
  cd tmp/docker

  mkdir -p ${CLANG_BIN_DIR}
  mkdir -p ${CLANG_LIB_DIR}
  mkdir -p ${CLANG_INCLUDE_DIR}
  mkdir -p ${CLANG_LS_DIR}

  docker cp "temp-llvmez80:/src/docker-shims/." "${CLANG_BIN_DIR}"
  docker cp "temp-llvmez80:/src/direct-shims/." "${CLANG_BIN_DIR}"
  docker cp "temp-llvmez80:/src/lib/." "${CLANG_LIB_DIR}"
  docker cp "temp-llvmez80:/src/include/." "${CLANG_INCLUDE_DIR}"
  docker cp "temp-llvmez80:/src/linker-scripts/." "${CLANG_LS_DIR}"

  eval "echo \"$ALIASES\"" > "$ENV_FILE"

  cd opt/clang-for-rc
  zip -r ../../../ez80-clang-docker.zip ./*
}

# Run functions in parallel
make_direct_zip &
main_docker_zip &

# Wait for both functions to complete
wait
