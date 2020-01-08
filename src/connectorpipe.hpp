#ifndef __CONNECTORPIPE_HPP__
#define __CONNECTORPIPE_HPP__

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "base.hpp"

class ConnectorPipe : public Base
{
private:
    Base* LeftExec;
    Base* RightExec;

public:
    ConnectorPipe(Base* left, Base* right) : LeftExec(left), RightExec(right){};

    virtual int execute()
    {
	int fds[2];
	int pipeReturn = pipe(fds);
	int leftRun, rightRun = -1;

	if (pipeReturn == -1)
	{
	    perror("pipe failed");
	    return -1;
	}

	pid_t pid = fork();
	if (pid == -1)
	{
	    perror("fork failed");
	    return -1;
	}
	else if (pid == 0) //child process
	{
	    //send output to write to the pipe
	    int savedup = dup(STDOUT_FILENO);
	    dup2(fds[1], STDOUT_FILENO);
	    close(fds[0]);
	    close(fds[1]);
	    leftRun = LeftExec->execute();
	    dup2(savedup, STDOUT_FILENO);

	    if (leftRun == 0)
	    {
		exit(0);
	    }
	    else
	    {
		exit(-1);
	    }
	}
	else if (pid > 0) //parent process
	{
	    int status;
	    pid_t waitReturn = waitpid(pid, &status, 0);
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

	    //read input from the pipe
	    int savedup = dup(STDIN_FILENO);
	    dup2(fds[0], STDIN_FILENO);
	    close(fds[0]);
	    close(fds[1]);
	    rightRun = RightExec->execute();
	    dup2(savedup, STDIN_FILENO);
	    
	    if (rightRun == 0)
	    {
		return 0;
	    }
	    else
	    {
		return -1;
	    }
	}

	return -1; //should never reach here
    }
};

#endif
