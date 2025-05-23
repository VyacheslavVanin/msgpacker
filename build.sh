#!/bin/bash
mkdir -p build
cd build
time (
    time cmake \
        -DCMAKE_BUILD_TYPE=release \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=yes \
        ..
    time make -j
    cp compile_commands.json ..
)