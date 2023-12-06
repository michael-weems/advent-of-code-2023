#!/bin/zsh

rm -f "$1"
clear

cc "$1.c" -o solution.out

./solution.out
