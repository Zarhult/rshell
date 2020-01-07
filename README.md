# CS 100 Programming Project                                                                                                                    
Fall Quarter 2019</br>
Francisco Maldonado (SID 862121095),  Calvin Glisson (SID 861257707)
# Introduction
Our project is a command shell ("RShell"). It prints a command prompt, reads in a line of commands/connectors from standard input, and executes them via `fork()`, `execvp()`, and `waitpid()`. Commands are formatted as `$ executable [argumentList] [connector] [executable] ...` where items in brackets are optional. Valid commands include anything in $PATH, as well as the `test` command which is described in the "Classes" section. RShell also supports use of parentheses to enclose certain strings of commands as a single entity.

We implemented the composite design pattern, with an abstract base class from which we derive executable command classes (Exe and Test) and connectors. User input is parsed to identify which commands and connectors are desired, initialized as the relevant classes, and executed in the appropriate order.
# Diagram
![OMT_Diagram](https://github.com/cs100/assignment-meme_team/blob/master/images/omt.png?raw=true)
# Classes
We use a base class that the executable and connector classes derive from. The base class has a pure virtual function `execute()` used by all derivative classes. The executable class (Exe), in this inherited `execute()` function, performs a syscall to run the specified command, such as `ls -la`, in addition to handling input/output redirection and `test` executions. The connector classes use two base class reference data members, which are used in the connector `execute()` functions to perform the appropriate executions in order (such as running `ls` and then, if `ls` succeeds, running `pwd` for an input of `ls && pwd`). Notably among the connectors is the pipe connector which not only executes the commands in order and returns success/failure but also pipes the output of the left executable to the right executable using the syscall `pipe`. Finally, there is the test object class (Test) which provides functionality for checking whether a file is present, whether it is a directory, and whether it is a regular file. This class takes both the syntax `test -e file` and `[ -e file ]`, each of which check whether "file" exists and print `(True)` or `(False)` accordingly. These can be used with connectors as you would expect, i.e. `test -e file && echo exists` would echo `exists` if "file" exists.
# Prototypes
(This section was written when were experimenting with the syscall functions `waitpid()`, `fork()`, and `execvp()`)</br>
We found out the basic uses of the three functions and how to implement them. First, `waitpid()` allows us to wait for a process with a given PID to end, and store various kinds of information regarding how it ended in an integer pointer. `fork()`, on the other hand, lets us run an entirely new process from the current process, and the code run by the new process can be decided by placing it within an `if (newProcess == 0) {}` statement, where `newProcess` is the `pid_t` return value of `fork()`. Finally, `execvp()` essentially allows us to run another executable from within the current process. It is designed to work for C, and uses a const char* array in place of a string, which is forbidden in C++. With some research we found that a useful hotfix for this is to cast the const char* array with a `(char* const*)` in front of the array name in the second argument of the `execvp()` call.

Using these functions, we will be able to execute files in $PATH, as well as create new processes and wait for them as needed in the operation of our shell.

As for the connectors, the && connector will execute the right command only if the left command was able to finish successfully.
The || connector will execute the right command only when the left command was not able to finish successfully.
The ; connector allows multiple commands to be placed on the same line, but still be treated as separate commands as if they were on seperate lines.
</br>
:octocat:
