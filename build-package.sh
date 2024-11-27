#!/usr/bin/env bash

set -e

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

export DOCKER_BUILDKIT=1

CLANG_BIN_DIR="opt/ez80-clang/bin"
CLANG_LIB_DIR="opt/ez80-clang/lib/"
CLANG_INCLUDE_DIR="opt/ez80-clang/include/"
CLANG_LS_DIR="opt/ez80-clang/linker-scripts/"
ENV_FILE="ez80-clang"

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

function make_direct_tar() {
  rm -rf tmp/direct
  mkdir -p tmp/direct/ez80-clang-${EZ80_CLANG_VERSION}
  cd tmp/direct/ez80-clang-${EZ80_CLANG_VERSION}

  mkdir -p ${CLANG_BIN_DIR}
  mkdir -p ${CLANG_LIB_DIR}
  mkdir -p ${CLANG_INCLUDE_DIR}
  mkdir -p ${CLANG_LS_DIR}

  cp ../../opt/ez80-clang/bin/* "${CLANG_BIN_DIR}"
  cp ../../../direct-shims/* ${CLANG_BIN_DIR}
  cp ../../../lib/* "${CLANG_LIB_DIR}"
  cp -r ../../opt/ez80-clang/include/* "${CLANG_INCLUDE_DIR}"
  cp -r ../../../include/* "${CLANG_INCLUDE_DIR}"
  cp ../../../linker-scripts/* "${CLANG_LS_DIR}"

  eval "echo \"$ALIASES\"" > "$ENV_FILE"
  cp ../../../install.sh .

  cd ..

  if command -v pigz &> /dev/null; then
    tar -cf - ez80-clang-${EZ80_CLANG_VERSION}/* | pigz  > ../../ez80-clang-${EZ80_CLANG_VERSION}.tar.gz
  else
    tar -czvf ../../ez80-clang-${EZ80_CLANG_VERSION}.tar.gz ez80-clang-${EZ80_CLANG_VERSION}/*
  fi

}

make_direct_tar
