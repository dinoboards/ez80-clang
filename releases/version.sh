export EZ80_CLANG_TOOLCHAIN_VERSION="0.0.14"
export EZ80_CLANG_TOOLCHAIN_PLATFORM="dinoboards/llvmez80-platform:${EZ80_CLANG_TOOLCHAIN_VERSION}"
export EZ80_CLANG_TOOLCHAIN_BUILDER="dinoboards/llvmez80-builder:${EZ80_CLANG_TOOLCHAIN_VERSION}"

export EZ80_CLANG_TOOLCHAIN_CACHE_FROM=""

export PREVIOUS_EZ80_CLANG_VERSION=$(git tag -l 'v0.[0-9]*.[0-9]*' | grep -E '^v[0-9]+\.[0-9]+\.[0-9]+$' | sort -V | tail -n 1)

if [ -z "$GITHUB_ACTIONS" ]; then
  IFS='.' read -r major minor patch <<< "$PREVIOUS_EZ80_CLANG_VERSION"

  EZ80_CLANG_VERSION="${major}.${minor}.${patch}-rc"

else

IFS='.' read -r major minor patch <<< "$PREVIOUS_EZ80_CLANG_VERSION"

if [[ "$GITHUB_REF" == "refs/heads/main" ]]; then
  patch=$((patch + 1))
  EZ80_CLANG_VERSION="${major}.${minor}.${patch}"
else
  IFS='.' read -r major minor patch <<< "$PREVIOUS_EZ80_CLANG_VERSION"

  EZ80_CLANG_VERSION="${major}.${minor}.${patch}-rc.${GITHUB_RUN_NUMBER}"
fi

fi
