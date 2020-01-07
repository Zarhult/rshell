#!/bin/bash

script_dir=$(dirname $0)

echo 'This script will (and should) fail if you run it outside of the project root'
INPUTS=('test -e src; test -d src; test -f src; exit'
        'test -e rshell; test -d rshell; test -f rshell; exit'
        'test -e src/main.cpp; test -d src/main.cpp; test -f src/main.cpp; exit'
	'(test -d src && test -e rshell) || echo "TEST FAILED"; exit'
)

for input in "${INPUTS[@]}"
do
    echo "\"${input}\" gives:" 
    echo "${input}" | "$script_dir"/../rshell
done
