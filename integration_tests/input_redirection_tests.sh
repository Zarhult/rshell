#!/bin/bash

script_dir=$(dirname $0)

INPUTS=('cat < names.txt; exit'
	'cat < README.md; exit'
	'cat < CMakeLists.txt; exit'
	)

for input in "${INPUTS[@]}"
do
    echo "\"${input}\" gives:" 
    echo "${input}" | "$script_dir"/../rshell
done
