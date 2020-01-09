#include <iostream>
#include <vector>
#include <string>

bool validParens(std::vector<std::string> &inputs)
{
    int numOfOpenP = 0;
    int numOfCloseP = 0;
    for (int i = 0; i < inputs.size(); ++i) 
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
