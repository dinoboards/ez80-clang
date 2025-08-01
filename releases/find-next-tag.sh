#!/bin/bash

set -e


PREVIOUS_VERSION=$(git tag -l 'v0.0.[0-9]*' | grep -E '^v[0-9]+\.[0-9]+\.[0-9]+$' | sort -V | tail -n 1)

IFS='.' read -r major minor patch <<< "$PREVIOUS_VERSION"
patch=$((patch + 1))

NEXT_VERSION="${major}.${minor}.${patch}"

export PREVIOUS_EZ80_CLANG_VERSION=$PREVIOUS_VERSION
export EZ80_CLANG_VERSION=$NEXT_VERSION

export PREVIOUS_VERSION
export NEXT_VERSION
