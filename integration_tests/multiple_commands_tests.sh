#!/bin/bash

script_dir=$(dirname $0)

INPUTS=('mkdir test; ls; rm -r test; ls; exit' 'ls "-la"; echo "this should print" || echo "this should not print"; exit' 'echo "this should print 1" && echo "this should print 2" || echo "this should not print"; exit')

for input in "${INPUTS[@]}"
do
    echo "\"${input}\" gives:" 
    echo "${input}" | "$script_dir"/../rshell
done
