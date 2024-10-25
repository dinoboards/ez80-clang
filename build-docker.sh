#!/usr/bin/env bash

# Source the version.sh file from the same directory
SCRIPT_DIR=$(dirname "$0")
source "$SCRIPT_DIR/version.sh"

docker build --progress plain -t ${EZ80_CLANG_TOOLCHAIN_VERSION} .

# docker run -v ${PWD}:/src/ -u $(id -u ${USER}):$(id -g ${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION}
