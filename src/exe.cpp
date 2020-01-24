#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "base.hpp"
#include "test.hpp"
#include "exe.hpp"
    
Exe::Exe(std::vector<std::string> cmd) : Base(), cmd(cmd) {};

void Exe::AppendRedirect(std::vector<std::string> &cmd) 
{
    //Convert filename to c-string
    std::string fileName = cmd.at(cmd.size() - 1);
    char cstring[fileName.length() + 1];
    strcpy(cstring, fileName.c_str());

    int newOut = open(cstring, O_WRONLY|O_APPEND|O_CREAT, 0777);
    savedup = dup(1);
    close(1);
    dup(newOut);
    outputRedirection = true;
    cmd.pop_back();
    return;
}

void Exe::InputRedirect(std::vector<std::string> &cmd) 
{
    //Convert filename to c-string
    std::string fileName = cmd.at(cmd.size() - 1); 
    char cstring[fileName.length()+1];
    strcpy(cstring, fileName.c_str());

    newIn = open(cstring, O_RDONLY);
    savedup = dup(0); //Save default state for input
    close(0);
    dup(newIn); //Change input to our file
    inputRedirection = true;
    cmd.pop_back(); //Remove file name from cmd list for executables
    return;
}

void Exe::OutputRedirect(std::vector<std::string> &cmd) //Same as input but with output instead
{   
    //Convert filename to c-string
    std::string fileName = cmd.at(cmd.size() - 1);
    char cstring[fileName.length() + 1];
    strcpy(cstring, fileName.c_str());

    int newOut = open(cstring, O_WRONLY|O_CREAT, 0777); //Change to O_CREAT | O_WRONLY when piping is done
    savedup = dup(1);
    close(1);
    dup(newOut);
    outputRedirection = true;
    cmd.pop_back();
    return;
}

void Exe::fixInputRedirection () 
{
    //close(newIn);
    dup2(savedup, 0); //Return to normal input
}

void Exe::fixOutputRedirection() 
{
    //close(newOut);
    dup2(savedup, 1); //Return to normal output
} 

int Exe::execute()
{
    inputRedirection = false;
    outputRedirection = false;

    //this is to test the cmd vector is created properly
    /*for (int i = 0; i < cmd.size(); ++i)
    {
	cout << cmd.at(i) << " ";
    }
    cout << endl;*/

    for (int i = 0; static_cast<unsigned long>(i) < cmd.size(); ++i) {
	if(cmd.at(i) == "<") {
	    cmd.erase(cmd.begin() + i);
	    InputRedirect(cmd);
	    break;
	} else if(cmd.at(i) == ">") {
	    cmd.erase(cmd.begin() + i);
	    OutputRedirect(cmd);
	    break;
	} else if(cmd.at(i) == ">>") {
	    cmd.erase(cmd.begin() + i);
	    AppendRedirect(cmd);
	    break;
	}
    }

    //handle exit exes
    if (cmd.at(0) == "exit") //if it's an exit command, just return to kill main
    {
	//cout << "About to exit" << endl;
	exit(0);
    }
    else
    {
	//handle test exes
	if (cmd.at(0) == "test" || cmd.at(0) == "[")
	{
	    std::vector<std::string> testCmd;
	    for (int i = 1; static_cast<unsigned long>(i) < cmd.size(); ++i)
	    { //Remove the test word and the [ ] symbols from cmd
		if (cmd.at(i) != "]")
		{
		    testCmd.push_back(cmd.at(i));
		}
	    }

	    Base *test = new Test(testCmd); //Make the test executable with the vector of strings with just the filename/flag

	    int t = test->execute(); //Returns 0 for true and -1 for false
	    if (t == 0)
	    {
		std::cout << "(True)" << std::endl;
	    }
	    else
	    {
		std::cout << "(False)" << std::endl;
	    }
	    return t; //Return the value so it works with connectors
	}

	//handle other exes
	const char *args[cmd.size() + 1]; //convert vector of string commands to c strings for the execvp function
	for (int i = 0; static_cast<unsigned long>(i) < cmd.size(); ++i)
	{
	    args[i] = cmd.at(i).c_str();
	}
	args[cmd.size()] = NULL;

	pid_t pid = fork();

	if (pid == -1)
	{
	    perror("fork failed");
	    return -1;
	}

	if (pid > 0)
	{ //in parent process, wait for forked process to end, and return -1 if forked process returns -1
	    int status;
	    pid_t waitReturn = waitpid(pid, &status, 0);
	    if (inputRedirection) {
		fixInputRedirection();
	    } else if (outputRedirection) {
		fixOutputRedirection();
	    }

	    if (waitReturn == -1)
	    {
		perror("waitpid() failed");
		return -1;
	    }
	    if (status != 0)
	    {
		perror("process waiting for failed");
		return -1;
	    }
	}
	else if (pid == 0)
	{ //in child process, run the executable
	    int exeReturn = execvp(args[0], (char *const *)args);
	    if (exeReturn == -1)
	    {
		perror("execvp() failed");
		exit(-1); //so that the waitpid() in the parent process will set status to a nonzero number if child fails
	    }
	}
	return 0;
    }
}

