#!/usr/bin/env bash

set -e

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

export  DOCKER_BUILDKIT=1

docker push ${EZ80_CLANG_TOOLCHAIN_PLATFORM}
docker push ${EZ80_CLANG_TOOLCHAIN_BUILDER}
