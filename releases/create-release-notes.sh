#!/bin/bash

set -e

# Define the release file path
relfile="./CHANGELOG.md"

# Remove the release file if it exists
rm -f "$relfile"

cat >> ${relfile}<< EOF
## Release ${EZ80_CLANG_VERSION}
-----------------------------

To install, for linux or for windows, use WSL:

\`\`\`
wget https://github.com/dinoboards/ez80-clang/releases/download/${EZ80_CLANG_VERSION}/ez80-clang-${EZ80_CLANG_VERSION}.tar.gz
tar -xzvf ez80-clang-${EZ80_CLANG_VERSION}.tar.gz
cd ez80-clang-${EZ80_CLANG_VERSION}
sudo ./install.sh
\`\`\`

EOF


# Create the release notes file
echo -e "### Release Notes\n\n" >> "$relfile"
echo "``````" >> "$relfile"

# Append the git log to the release notes file
gitLog=$(git log --pretty=format:"%ad: %s" --date=short --submodule=short "$PREVIOUS_EZ80_CLANG_VERSION..$HEAD")
echo "$gitLog" >> "$relfile"

# Output the last release tag
echo "Created ./releases/CHANGELOG.md detailing changes from '${PREVIOUS_EZ80_CLANG_VERSION}' to '${EZ80_CLANG_VERSION}'"
