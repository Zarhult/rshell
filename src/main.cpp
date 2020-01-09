#include <iostream>
#include <string>
#include <vector>
#include "parser.hpp"
#include "nightmare.hpp"
#include "validparens.hpp"

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
