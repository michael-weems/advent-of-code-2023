#!/bin/zsh

rm -f tests.out
clear

cc part1.tests.c -o tests.out

./tests.out
