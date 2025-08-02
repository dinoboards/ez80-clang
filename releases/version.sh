export EZ80_CLANG_TOOLCHAIN_VERSION="0.0.14"
export EZ80_CLANG_TOOLCHAIN_PLATFORM="dinoboards/llvmez80-platform:${EZ80_CLANG_TOOLCHAIN_VERSION}"
export EZ80_CLANG_TOOLCHAIN_BUILDER="dinoboards/llvmez80-builder:${EZ80_CLANG_TOOLCHAIN_VERSION}"

export EZ80_CLANG_TOOLCHAIN_CACHE_FROM=""

if [ -z "$GITHUB_ACTIONS" ]; then
  export EZ80_CLANG_VERSION="v0.0.x"
  export PREVIOUS_EZ80_CLANG_VERSION=$(git tag -l 'v0.0.[0-9]*' | grep -E '^v[0-9]+\.[0-9]+\.[0-9]+$' | sort -V | tail -n 1)

elif [[ "$GITHUB_REF" == refs/tags/* ]]; then
  export EZ80_CLANG_VERSION="${GITHUB_REF#refs/tags/}"
  export PREVIOUS_EZ80_CLANG_VERSION=$(git tag -l 'v0.0.[0-9]*' | grep -E '^v[0-9]+\.[0-9]+\.[0-9]+$' | sort -V | tail -n 2 | head -n 1)

else
  export PREVIOUS_EZ80_CLANG_VERSION=$(git tag -l 'v0.0.[0-9]*' | grep -E '^v[0-9]+\.[0-9]+\.[0-9]+$' | sort -V | tail -n 1)

  RC_NUMBER="${GITHUB_RUN_NUMBER}"
  # Get the SHA of the latest tag
  LATEST_TAG_SHA=$(git rev-list -n 1 "$PREVIOUS_EZ80_CLANG_VERSION")

  # Check if the current commit is tagged with a version
  if [ "$LATEST_TAG_SHA" = "$CURRENT_SHA" ]; then
    EZ80_CLANG_VERSION="$PREVIOUS_EZ80_CLANG_VERSION"
  else
    EZ80_CLANG_VERSION="${PREVIOUS_EZ80_CLANG_VERSION}-rc.${RC_NUMBER}"
  fi
fi

