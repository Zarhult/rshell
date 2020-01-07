#!/bin/bash

script_dir=$(dirname $0)

INPUTS=('ls | grep s; exit'
	'echo "piping" | tee pipingFile && cat pipingFile && rm pipingFile; exit'
	'cat < src/main.cpp | tr A-Z a-z | grep nightmare; exit'
	'echo longPipe | tr A-Z a-z | tr a-z A-Z | tr A-Z a-z | tr a-z A-Z | tr A-Z a-z | tr a-z A-Z | tr A-Z a-z | tee out && cat out && rm out; exit'
	'(((ls "-la") && (cat < src/main.cpp | tr a-z A-Z | tee out && cat out) && rm out)); (exit)'
	)

for input in "${INPUTS[@]}"
do
    echo "\"${input}\" gives:" 
    echo "${input}" | "$script_dir"/../rshell
done
