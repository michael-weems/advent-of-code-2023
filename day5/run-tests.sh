#!/bin/zsh

rm -f tests.out
clear

cc 1.tests.c -o tests.out

./tests.out
