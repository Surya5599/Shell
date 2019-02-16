#!/bin/sh

source shell.cpp

INPUTS=("echo hello" "ls")

echo "Executing ./c-echo ${INPUTS[0]}"
./rshell ${INPUTS[0]}



