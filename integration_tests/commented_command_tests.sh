#!/bin/bash

script_dir=$(dirname $0)

INPUTS=('ls; exit; #echo "do not print this"' 'echo "Hello" && exit && echo "should not be here" #Dont even try to print this' 'echo "yeet"; exit #We are done if this works')

for input in "${INPUTS[@]}"
do 
    echo "\"${input}\" | ./rshell"
    echo "${input}" | "$script_dir"/../rshell
done
