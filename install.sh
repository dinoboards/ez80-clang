#!/bin/bash

# Check if the script is run as root or with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script as root or with sudo."
  exit 1
fi

set -e

rm -rf /opt/ez80-clang
cp -r opt/* /opt/

#move file ${EZ80_CLANG_DIR}/ez80-clang to SUDO_USER/.ez80-clang

USER_HOME=$(eval echo "~$SUDO_USER")
ENV_FILE="${USER_HOME}/.ez80-clang"

cp ez80-clang $ENV_FILE
chown "$SUDO_USER:$SUDO_USER" "$ENV_FILE"
chmod 644 "$ENV_FILE"

echo "Environrment variables defined in: $ENV_FILE"
echo "Tools installed into: /opt/ez80-clang"

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
