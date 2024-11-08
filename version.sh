export EZ80_CLANG_TOOLCHAIN_VERSION="0.0.10"
export EZ80_CLANG_TOOLCHAIN_PLATFORM="dinoboards/llvmez80-platform:${EZ80_CLANG_TOOLCHAIN_VERSION}"
export EZ80_CLANG_TOOLCHAIN_BUILDER="dinoboards/llvmez80-builder:${EZ80_CLANG_TOOLCHAIN_VERSION}"

export EZ80_CLANG_TOOLCHAIN_CACHE_FROM="--cache-from=dinoboards/llvmez80-builder:0.0.4 --cache-from=dinoboards/llvmez80:0.0.4 --cache-from=dinoboards/llvmez80-platform:0.0.4"

