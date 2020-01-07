#!/bin/bash

script_dir=$(dirname $0)

INPUTS=('ls asdf || (echo a && echo b) && ls asdf || echo c; (echo d || echo error); exit'
        '(echo a && (ls asdf || (echo b && echo c))) && (echo d; (ls asdf || (echo e; echo d && (echo f && echo g)))) && (ls || (echo fail && echo fail || (echo fail && echo fail))); (exit)'
        '(echo a && (echo b && echo c)); echo d; exit'
        'echo a && (echo b; (echo c && echo d)); (exit)'
)

for input in "${INPUTS[@]}"
do
    echo "\"${input}\" gives:" 
    echo "${input}" | "$script_dir"/../rshell
done
