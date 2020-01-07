#include <iostream>
#include <vector>
#include <string>

bool validParens(std::vector<std::string> &inputs)
{
    int numOfP = 0;
    for (int i = 0; i < inputs.size(); ++i) 
    {
        if(inputs.at(i) == "(" || inputs.at(i) == ")") 
	{
		++numOfP;
	}
    }
    if ((numOfP % 2) != 0) 
    {
	std::cout << "Error: uneven number of parentheses" << std::endl;
	return false;
    }
    else
    {
	return true;
    }
}
