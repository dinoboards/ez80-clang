#!/usr/bin/env bash

set -e

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

# Variables
REPO="dinoboards/llvm-project"
TAG="v${EZ80_CLANG_TOOLCHAIN_VERSION}"
RELEASE_NAME="Clang Release $TAG"
TAR_FILE="release.${EZ80_CLANG_TOOLCHAIN_VERSION}.tar.gz"
TARGET_DIR="tmp/opt/ez80-clang"
BRANCH="ez80-for-rc-clang-tool-chain"

# Create a tar file containing all the files in tmp/opt/ez80-clang
tar -czvf $TAR_FILE -C $TARGET_DIR .

# Create a GitHub draft release and upload the tar file

gh release create $TAG $TAR_FILE --repo $REPO --title "$RELEASE_NAME" --prerelease --notes "Draft release for $RELEASE_NAME" --target $BRANCH

echo "Draft release created successfully."
