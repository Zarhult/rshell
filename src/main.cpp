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
    getline(std::cin, command);
    while (command != "exit")
    {
	std::vector<std::string> inputs = parse(command);

	if (validParens(inputs))
	{
	    Base* connector = nightmare(inputs);
	    connector->execute();
	}
        
	std::cout << "$ ";
        getline(std::cin, command);
    }

    return 0;
}
