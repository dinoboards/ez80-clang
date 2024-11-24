#!/usr/bin/env bash

set -e

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

export DOCKER_BUILDKIT=1

CLANG_BIN_DIR="./tmp/opt/ez80-clang/bin"
CLANG_INCLUDE_DIR="./tmp/opt/ez80-clang/include/"

docker rm -f temp-llvmez80 > /dev/null 2>&1
trap 'docker rm -f temp-llvmez80  > /dev/null 2>&1' EXIT
docker create --name temp-llvmez80 ${EZ80_CLANG_TOOLCHAIN_BUILDER} > /dev/null 2>&1

rm -rf "./tmp/opt"
mkdir -p ${CLANG_BIN_DIR}
mkdir -p ${CLANG_INCLUDE_DIR}

docker cp "temp-llvmez80:/opt/ez80-clang/bin/." "${CLANG_BIN_DIR}"
cp ./direct-shims/* ${CLANG_BIN_DIR}

docker cp "temp-llvmez80:/src/include/." "${CLANG_INCLUDE_DIR}"
