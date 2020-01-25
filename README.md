# rshell                                                                                                                
rshell is a simple shell originally created collaboratively by me and a classmate for CS100 at UCR. It supports execution of commands in $PATH and standard bash connectors like `&&`, `||`, and `;`, as well as IO redirection/piping with `<`, `>`, and `|`. There is also a `test` function to check whether a file exists with the `-e` flag, whether a file is a directory with the `-d` flag, and whether a file is a regular file with the `-f` flag. Unlike the GNU test command, `test` will also output `(True)` or `(False)` depending on the result. For example, `test -d src` would output `(True)` and return true if you were in the repo's root directory. The syntax `[ -d src ]` is also supported. In addition, parentheses are supported for control of precedence, as in `(echo a && echo b) || echo c`, and quotes can be used as in `echo "hi"`. Anything after a `#` is treated as a comment and ignored. Finally, the shell can be exited by running `exit`.
# Setup
```
git clone --recurse-submodules https://github.com/Zarhult/rshell.git
cd rshell
cmake .
make
```
This will generate the `rshell` executable as well as a `test` executable that runs the unit tests.
