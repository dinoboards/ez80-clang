#!/bin/bash

set -e

gh release create ${EZ80_CLANG_VERSION} --draft --title "$version" -F ./CHANGELOG.md "../ez80-clang-${EZ80_CLANG_VERSION}.tar.gz"

echo "Created Github Release '${EZ80_CLANG_VERSION}'"

