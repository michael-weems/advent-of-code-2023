#!/bin/zsh

rm -f solution.out
clear

cc "$1.c" -o solution.out

./solution.out "$2"
