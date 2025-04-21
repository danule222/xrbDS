#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_ROOT/build"

WORKING_DIR_NAME="$(basename "$SCRIPT_DIR")"

if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR" || {
    echo "build/ directory could not be created. Exiting..."
    exit 3
  }
fi

echo "Installing Conan dependencies..."
conan install "$PROJECT_ROOT" \
  --profile:host=nds \
  --profile:build=nds \
  --build=missing \
  --output-folder="$BUILD_DIR"

echo "Generating CMake solution..."
cd "$PROJECT_ROOT" || exit 1
cmake --preset conan-release
