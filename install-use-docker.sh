#!/bin/bash

# Set up the clang tool chain required for compling for the ez80 on the RCBus/RC2014 platform
# uses a docker image with local shims
# requires docker
# and probably bash
# not test on osx
# works on WSL2 (Ubuntu)

# Check if the script is run as root or with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script as root or with sudo."
  exit 1
fi

SCRIPT_DIR=$(dirname "$0")
SCRIPT_DIR=$(cd "${SCRIPT_DIR}/" && pwd)/

source "$SCRIPT_DIR/version.sh"  "${SCRIPT_DIR}"

docker rm -f temp-llvmez80 > /dev/null 2>&1
trap 'docker rm -f temp-llvmez80  > /dev/null 2>&1' EXIT
docker create --name temp-llvmez80 ${EZ80_CLANG_TOOLCHAIN_BUILDER} > /dev/null 2>&1

CLANG_BIN_DIR="/opt/clang-for-rc/bin/"
CLANG_LIB_DIR="/opt/clang-for-rc/lib/"
CLANG_INCLUDE_DIR="/opt/clang-for-rc/include/"

cd /tmp

set -e
sudo rm -rf ${CLANG_BIN_DIR}
sudo rm -rf ${CLANG_LIB_DIR}
sudo rm -rf ${CLANG_INCLUDE_DIR}

sudo mkdir -p ${CLANG_BIN_DIR}
sudo mkdir -p ${CLANG_LIB_DIR}
sudo mkdir -p ${CLANG_INCLUDE_DIR}

docker cp "temp-llvmez80:/src/docker-shims/." "${CLANG_BIN_DIR}"
docker cp "temp-llvmez80:/src/lib/." "${CLANG_LIB_DIR}"
docker cp "temp-llvmez80:/src/include/." "${CLANG_INCLUDE_DIR}"

# ENV vars required
ALIASES=$(cat << 'EOF'
export EZ80_CLANG_SYSTEM_INCLUDE_PATH=${CLANG_INCLUDE_DIR}
export EZ80_CLANG_LIB_PATH=${CLANG_LIB_DIR}

if [[ ":\$PATH:" != *":${CLANG_BIN_DIR}:"* ]]; then
    export PATH="\${PATH}:${CLANG_BIN_DIR}"
fi

EOF
)

USER_HOME=$(eval echo "~$SUDO_USER")
ENV_FILE="${USER_HOME}/.ez80-clang"

eval "echo \"$ALIASES\"" > "$ENV_FILE"
chown "$SUDO_USER:$SUDO_USER" "$ENV_FILE"
chmod 644 "$ENV_FILE"

echo "Environrment variables defined in: $ENV_FILE"

# Ensure ~/ez80-clang-aliases is sourced in the appropriate shell configuration files
ensure_aliases_sourced() {
    local file=$1
    if ! grep -q "source ${ENV_FILE}" "$file"; then
        echo -e "\nsource ${ENV_FILE}" >> "$file"
        echo "Added source ${ENV_FILE} to $file"
    fi
}

# Determine the OS and ensure ~/ez80-clang-aliases is sourced in the appropriate file
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    if [ -n "$ZSH_VERSION" ]; then
        ensure_aliases_sourced "$USER_HOME/.zshrc"
    else
        ensure_aliases_sourced "$USER_HOME/.bashrc"
    fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
    ensure_aliases_sourced "$USER_HOME/.bash_profile"
    ensure_aliases_sourced "$USER_HOME/.zshrc"
else
    echo "Unsupported OS: $OSTYPE"
    exit 1
fi
