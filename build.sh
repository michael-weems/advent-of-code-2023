#!/bin/zsh

build_dir="$1"

pushd "$build_dir"

make clean
make

popd
