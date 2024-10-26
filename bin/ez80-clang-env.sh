export EZ80_CLANG_TOOLCHAIN_VERSION="dinoboards/llvmez80:0.0.2"

export CLANG_INCLUDE_PATH=$(cd "$1/../includes/" && pwd)/
export CLANG_SYSTEM_INCLUDE_PATH=${CLANG_INCLUDE_PATH}clang/15.0.0/

export CLANG_DOCKER_OPTIONS="-v ${CLANG_SYSTEM_INCLUDE_PATH}:${CLANG_SYSTEM_INCLUDE_PATH} -v ${CLANG_INCLUDE_PATH}:${CLANG_INCLUDE_PATH} -w /host/${PWD} -v /:/host/ -u $(id -u ${USER}):$(id -g ${USER})"

