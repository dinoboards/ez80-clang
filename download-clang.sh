#!/usr/bin/env bash

set -e

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

export DOCKER_BUILDKIT=1

CLANG_BIN_DIR="./tmp/opt/ez80-clang/bin"
CLANG_INCLUDE_DIR="./tmp/opt/ez80-clang/include/"

rm -rf "./tmp/opt"
rm -f ./tmp/release.*.tar.gz
mkdir -p ./tmp/opt/ez80-clang

cd tmp

wget "https://github.com/dinoboards/llvm-project/releases/download/v${EZ80_CLANG_TOOLCHAIN_VERSION}/release.${EZ80_CLANG_TOOLCHAIN_VERSION}.tar.gz"
tar -xvf release.${EZ80_CLANG_TOOLCHAIN_VERSION}.tar.gz -C ./opt/ez80-clang

