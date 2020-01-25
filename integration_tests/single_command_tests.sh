#!/bin/bash

script_dir=$(dirname $0)

INPUTS=('ls' 'mkdir testdir' 'rm -r testdir' 'echo "test"' 'pwd')

for input in "${INPUTS[@]}"
do
    echo "${input}" gives:
    ${input} < "$script_dir"/../rshell
done
