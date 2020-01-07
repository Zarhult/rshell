#!/bin/bash

script_dir=$(dirname $0)

INPUTS=('ls > file; cat < file; rm file; exit'
	'ls -a > file; cat < file; rm file; exit'
	'echo "Integration tests" > file; cat < file; rm file; exit'
	'echo passed > file; echo testing > file2; cat file file2 > new; cat < new; rm file; rm file2; rm new; exit'
	'echo Every >> file; echo word >> file; echo should >> file; echo be >> file; echo on >> file; echo a >> file; echo new >> file; echo line >> file; cat file; rm file; exit'
	'echo "About to append ls" > file; ls >> file; cat < file; rm file; exit'
	)

for input in "${INPUTS[@]}"
do
    echo "\"${input}\" gives:" 
    echo "${input}" | "$script_dir"/../rshell
done
