#!/bin/bash

DIR="../build"

if [ ! -d $DIR ]; then
  mkdir $DIR
fi

if [ ! -d $DIR ]; then
  echo "Failed to create build directory"
  exit 3
fi

if [ ! -d $DEVKITPRO ]; then
  echo "Please set DEVKITPRO environment variable"
  exit 2
fi

working_dir_name="$(basename "$PWD")"

if [ "$working_dir_name" = "tools" ]; then
  echo "Creating solution..."
else
  echo "Please run this script from the tools directory"
  exit 1
fi

$DEVKITPRO/portlibs/nds/bin/arm-none-eabi-cmake -S .. -B $DIR