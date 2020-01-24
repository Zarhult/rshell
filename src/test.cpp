#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "base.hpp"
#include "test.hpp"

Test::Test(std::vector<std::string> input) : Base(), cmd(input) {}

int Test::execute()
{
	std::string flag;
	std::string file;
	if (cmd.size() > 2)
	{ //If there are more than just a flag and file name
		std::cout << "Too many arguments" << std::endl;
		return -1;
	}
	else if (cmd.size() == 1)
	{ //If there are no flags or file names
		flag = "-e";
		file = cmd.at(0);
	}
	else if (cmd.size() == 2)
	{
		flag = cmd.at(0);
		file = cmd.at(1);
	}

	//It got past the sorting. Now has the flag and file name separated
	const char *c = file.c_str();
	struct stat buffer;
	int statReturn = stat(c, &buffer); //If the file exists
	if (statReturn == -1)
	{
		return -1;
	}

	if (flag == "-e")
	{ //Checks to see if the file exists
		return 0;
	}
	else if (flag == "-d")
	{ //Checks to see if the file is a directory
		if (S_ISDIR(buffer.st_mode) != 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else if (flag == "-f")
	{ //Checks to see if the file is a regular file
		if (S_ISREG(buffer.st_mode) != 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	return -1; //should never reach this line, but return to prevent compiler warnings
}

