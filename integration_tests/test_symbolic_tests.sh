#!/bin/bash

script_dir=$(dirname $0)

echo 'This script will (and should) fail if you run it outside of the project root'
INPUTS=('[ -e src ]; [ -d src ]; [ -f src ]; exit'
        '[ -e rshell ]; [ -d rshell ]; [ -f rshell ]; exit'
        '[ -e src/main.cpp ]; [ -d src/main.cpp ]; [ -f src/main.cpp ]; exit'
	'ls -la && ([ -d src ] || echo "TEST FAILED"); exit'
)

for input in "${INPUTS[@]}"
do
    echo "\"${input}\" gives:" 
    echo "${input}" | "$script_dir"/../rshell
done
