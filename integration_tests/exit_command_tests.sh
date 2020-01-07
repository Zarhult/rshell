#!/bin/bash

script_dir=$(dirname $0)

INPUTS=('ls; exit; echo "Should not print"' 'echo "Hello" && exit; echo "Should not print"' 'ls asdf || exit; echo "Should not print"')

for input in "${INPUTS[@]}"
do
    echo "\"${input}\" gives:" 
    echo "${input}" | "$script_dir"/../rshell
done
