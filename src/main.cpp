#include <iostream>
#include <string>
#include <vector>
#include "base.hpp"
#include "parser.hpp"
#include "nightmare.hpp"

bool validParens(std::vector<std::string> &inputs);

int main()
{
    std::string command;
    std::cout << "$ ";
    while (getline(std::cin, command))
    {
	std::vector<std::string> inputs = parse(command);

	if (validParens(inputs))
	{
	    Base* connector = nightmare(inputs);
	    connector->execute();
	}
	else
	{
	    std::cout << "ERROR: Missing open or closing parentheses." << std::endl;
	}
        
	std::cout << "$ ";
    }

    return 0;
}

bool validParens(std::vector<std::string> &inputs)
{
    int numOfOpenP = 0;
    int numOfCloseP = 0;
    for (int i = 0; static_cast<unsigned long>(i) < inputs.size(); ++i) 
    {
        if(inputs.at(i) == "(")
	{
	    ++numOfOpenP;
	}
	else if (inputs.at(i) == ")")
	{
	    ++numOfCloseP;
	}
    }
    if (numOfOpenP == numOfCloseP) 
    {
	return true;
    }
    else
    {
	return false;
    }
}

