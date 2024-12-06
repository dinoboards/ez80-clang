export EZ80_CLANG_TOOLCHAIN_VERSION="0.0.14"
export EZ80_CLANG_TOOLCHAIN_PLATFORM="dinoboards/llvmez80-platform:${EZ80_CLANG_TOOLCHAIN_VERSION}"
export EZ80_CLANG_TOOLCHAIN_BUILDER="dinoboards/llvmez80-builder:${EZ80_CLANG_TOOLCHAIN_VERSION}"

export EZ80_CLANG_TOOLCHAIN_CACHE_FROM=""

EZ80_CLANG_VERSION="0.0.0"


# Get the current branch name
BRANCH_NAME=$(git rev-parse --abbrev-ref HEAD)

# Clean up the branch name to be used in the version
CLEAN_BRANCH_NAME=$(echo "$BRANCH_NAME" | tr '/' '-' | tr -cd '[:alnum:]-')

# Get the latest tag that matches the pattern vx.x.x
LATEST_TAG=$(git tag -l 'v0.0.[0-9]*' | grep -E '^v[0-9]+\.[0-9]+\.[0-9]+$' | sort -V | tail -n 1)

# Get the current commit SHA
CURRENT_SHA=$(git rev-parse HEAD)

if [ -z "$GITHUB_ACTIONS" ]; then
  TIME=$(date +"%Y%m")
  USER=${SUDO_USER:-$USER}
  EZ80_CLANG_VERSION="${LATEST_TAG}-${USER}.${TIME}"

elif [[ "$GITHUB_REF" == refs/tags/* ]]; then
  EZ80_CLANG_VERSION="${GITHUB_REF#refs/tags/}"

else
  RC_NUMBER="${GITHUB_RUN_NUMBER}"
  # Get the SHA of the latest tag
  LATEST_TAG_SHA=$(git rev-list -n 1 "$LATEST_TAG")

  # Check if the current commit is tagged with a version
  if [ "$LATEST_TAG_SHA" = "$CURRENT_SHA" ]; then
    EZ80_CLANG_VERSION="$LATEST_TAG"
  else
  # elif [ "$BRANCH_NAME" = "main" ]; then
    EZ80_CLANG_VERSION="${LATEST_TAG}-rc.${RC_NUMBER}"
  # else
  #   EZ80_CLANG_VERSION="${LATEST_TAG}-${CLEAN_BRANCH_NAME}.${RC_NUMBER}"
  fi
fi

export LATEST_TAG
export EZ80_CLANG_VERSION
