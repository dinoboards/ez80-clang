#!/bin/bash


# Source the version.sh file from the same directory
SCRIPT_DIR=$(dirname "$0")
source "$SCRIPT_DIR/version.sh"

# Aliases to be added
ALIASES=$(cat << 'EOF'
alias ez80-tool-chain=\"docker run -v \${PWD}:/src/ -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION}\"
alias ez80-clang=\"docker run -v \${PWD}:/src/ -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} clang -target ez80-none-elf -nostdinc\"
alias ez80-objdump=\"docker run -v \${PWD}:/src/ -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} ez80-none-elf-objdump\"
alias ez80-ld=\"docker run -v \${PWD}:/src/ -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} ez80-none-elf-ld\"
alias ez80-as=\"docker run -v \${PWD}:/src/ -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} ez80-none-elf-as\"
alias ez80-ar=\"docker run -v \${PWD}:/src/ -u \$(id -u \${USER}):\$(id -g \${USER}) -it ${EZ80_CLANG_TOOLCHAIN_VERSION} ez80-none-elf-ar\"
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

echo "Aliases added: "
echo "  ez80-clang"
echo "  ez80-objdump"
echo "  ez80-ld"
echo ""
echo "Open a new terminal or run 'source ~/.bashrc' or 'source ~/.zshrc' to apply changes."
