
export CLANG_INCLUDE_PATH=/opt/clang-for-rc/include/
export CLANG_SYSTEM_INCLUDE_PATH=${CLANG_INCLUDE_PATH}clang/15.0.0/

export CLANG_DOCKER_OPTIONS="-v ${EZ80_CLANG_SYSTEM_INCLUDE_PATH}:${EZ80_CLANG_SYSTEM_INCLUDE_PATH} -w /host/${PWD} -v /:/host/ -u $(id -u ${USER}):$(id -g ${USER})"
