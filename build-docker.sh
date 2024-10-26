#!/usr/bin/env bash
# Source the version.sh file from the same directory
SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/
BIN_DIR="${SCRIPT_DIR}bin/"

source "$SCRIPT_DIR/bin/ez80-clang-env.sh"  "${BIN_DIR}"

docker build --progress plain -t ${EZ80_CLANG_TOOLCHAIN_VERSION} .

# docker run -v ${PWD}:/src/ -u $(id -u ${USER}):$(id -g ${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION}
