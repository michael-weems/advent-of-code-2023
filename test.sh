#!/bin/zsh

test_dir="$1"

program="$2"
if [ -z "$2" ]
then
    echo "Error: Program specification missing. Please specify which program to test as the second argument"
    exit 1;
fi

./build.sh "$run_dir"
sleep 2

pushd "$test_dir"
./$program.test.out
popd
