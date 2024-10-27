#!/usr/bin/env bash

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

echo "Building ${EZ80_CLANG_TOOLCHAIN_BUILDER}"
echo
docker build --target builder -t ${EZ80_CLANG_TOOLCHAIN_BUILDER} .

echo
echo "Building ${EZ80_CLANG_TOOLCHAIN_IMAGE}"
echo
docker build -t ${EZ80_CLANG_TOOLCHAIN_IMAGE} .

# docker run -v ${PWD}:/src/ -u $(id -u ${USER}):$(id -g ${USER}) -it ${EZ80_CLANG_TOOLCHAIN_BUILDER}
