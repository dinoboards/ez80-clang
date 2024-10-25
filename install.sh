#!/bin/bash



# Source the version.sh file from the same directory
SCRIPT_DIR=$(dirname "$0")
source "$SCRIPT_DIR/version.sh"


CLANG_INCLUDE_PATH=$(cd "${SCRIPT_DIR}/includes/" && pwd)/
CLANG_SYSTEM_INCLUDE_PATH=${CLANG_INCLUDE_PATH}clang/15.0.0/

export VOL_MAPS="-v \${CLANG_SYSTEM_INCLUDE_PATH}:\${CLANG_SYSTEM_INCLUDE_PATH} -v \${CLANG_INCLUDE_PATH}:\${CLANG_INCLUDE_PATH} -v \${PWD}:/src/ "

# Aliases to be added
ALIASES=$(cat << 'EOF'
alias ez80-tool-chain=\"docker run ${VOL_MAPS} -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION}\"
alias ez80-clang=\"docker run ${VOL_MAPS} -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} clang -target ez80-none-elf -nostdinc -isystem \${CLANG_INCLUDE_PATH} -isystem \${CLANG_SYSTEM_INCLUDE_PATH}\"
alias ez80-objdump=\"docker run ${VOL_MAPS} -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} ez80-none-elf-objdump\"
alias ez80-ld=\"docker run ${VOL_MAPS} -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} ez80-none-elf-ld\"
alias ez80-as=\"docker run ${VOL_MAPS} -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} ez80-none-elf-as\"
alias ez80-ar=\"docker run ${VOL_MAPS} -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} ez80-none-elf-ar\"

export CLANG_SYSTEM_INCLUDE_PATH=${CLANG_SYSTEM_INCLUDE_PATH}
export CLANG_INCLUDE_PATH=${CLANG_INCLUDE_PATH}
EOF
)

# Function to add aliases to a file if they don't already exist
add_aliases() {
    local file=$1
    if ! grep -q "ez80-clang" "$file"; then
        eval "echo \"$ALIASES\"" >> "$file"
        echo "Aliases added to $file"
    else
        eval "echo \"$ALIASES\"" > "$file"
        echo "Aliases updated in $file"
    fi
}

# Ensure ~/ez80-clang-aliases is sourced in the appropriate shell configuration files
ensure_aliases_sourced() {
    local file=$1
    if ! grep -q "source ~/.ez80-clang-aliases" "$file"; then
        echo -e "\nsource ~/.ez80-clang-aliases" >> "$file"
        echo "Added source ~/.ez80-clang-aliases to $file"
    fi
}

CLANG_INCLUDE_FILES=(
    "stdint.h"
    "stddef.h"
    "stdarg.h"
    "stdbool.h"
    "__stddef_max_align_t.h"
    "float.h"
)

install_system_include_files() {
     # Set an exit trap to remove the temporary container
    trap 'docker rm -f temp-llvmez80 > /dev/null 2>&1' EXIT

    # Build the Docker image up to the intermediate stage named "builder"
    docker build --target builder -t llvmez80-builder .  > /dev/null 2>&1

    docker create --name temp-llvmez80 llvmez80-builder  > /dev/null 2>&1

    rm -rf ${CLANG_SYSTEM_INCLUDE_PATH}
    mkdir -p ${CLANG_SYSTEM_INCLUDE_PATH}
    # Copy each file from the container to the host
    for file in "${CLANG_INCLUDE_FILES[@]}"; do
       docker cp -q "temp-llvmez80:/src/llvm-project/build/lib/clang/15.0.0/include/${file}" "${CLANG_SYSTEM_INCLUDE_PATH}${file}"
    done
}


# Add aliases to ~/ez80-clang-aliases
add_aliases "$HOME/.ez80-clang-aliases"

# Determine the OS and ensure ~/ez80-clang-aliases is sourced in the appropriate file
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    if [ -n "$ZSH_VERSION" ]; then
        ensure_aliases_sourced "$HOME/.zshrc"
    else
        ensure_aliases_sourced "$HOME/.bashrc"
    fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
    ensure_aliases_sourced "$HOME/.bash_profile"
    ensure_aliases_sourced "$HOME/.zshrc"
else
    echo "Unsupported OS: $OSTYPE"
    exit 1
fi

# Source the updated file to apply changes
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    if [ -n "$ZSH_VERSION" ]; then
        source "$HOME/.zshrc"
    else
        source "$HOME/.bashrc"
    fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
    if [ -n "$ZSH_VERSION" ]; then
        source "$HOME/.zshrc"
    else
        source "$HOME/.bash_profile"
    fi
fi

install_system_include_files

echo "Aliases added: "
echo "  ez80-clang"
echo "  ez80-objdump"
echo "  ez80-ld"
echo "  ez80-as"
echo "  ez80-ar"
echo ""
echo "Open a new terminal or run 'source ~/.bashrc' or 'source ~/.zshrc' to apply changes."
