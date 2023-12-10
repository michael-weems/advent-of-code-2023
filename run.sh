#!/bin/zsh

run_dir="$1"

program="$2"
if [ -z "$2" ]
then
    echo "Error: Program specification missing. Please specify which program to run as the second argument"
    exit 1;
fi

./build.sh "$run_dir"
sleep 2

data_file="$3"
if [ -z "$3" ]
then
    data_file="./input"
fi


pushd "$run_dir"
./$program.out
popd
