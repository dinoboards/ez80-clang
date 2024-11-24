#!/usr/bin/env bash

set -e

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

export  DOCKER_BUILDKIT=1

echo "Building ${EZ80_CLANG_TOOLCHAIN_PLATFORM}"
echo
docker build ${EZ80_CLANG_TOOLCHAIN_CACHE_FROM} --build-arg BUILDKIT_INLINE_CACHE=1 --target platform -t ${EZ80_CLANG_TOOLCHAIN_PLATFORM} .

echo "Building ${EZ80_CLANG_TOOLCHAIN_BUILDER}"
echo
docker build ${EZ80_CLANG_TOOLCHAIN_CACHE_FROM} --build-arg BUILDKIT_INLINE_CACHE=1 --target builder -t ${EZ80_CLANG_TOOLCHAIN_BUILDER} .

