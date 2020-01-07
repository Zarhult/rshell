# rshell                                                                                                                
rshell is a simple shell created collaboratively by me and a classmate for CS100 at UCR. It supports execution of commands in $PATH and standard bash connectors like `&&`, `||`, and `;`, as well as IO redirection/piping with `<`, `>`, and `|`. There is also a `test` function to check whether a file exists with the `-e` flag, whether a file is a directory with the `-d` flag, and whether a file is a regular file with the `-f` flag. For example, `test -d src` would return true in the repo's root directory. The syntax `[ -d src ]` is also supported. Parentheses are supported for control of precedence, as in `(echo a && echo b) || echo c`, and quotes can be used as in `echo "hi"`. Anything after a `#` is treated as a comment and ignored. Finally, the shell can be exited by running `exit`.
# Compilation
```
cmake .
make
```
