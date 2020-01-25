#include <string>
#include <vector>
#include "base.hpp"
#include "connectoror.hpp"
#include "connectorand.hpp"
#include "connectorsemicolon.hpp"
#include "connectorpipe.hpp"
#include "exe.hpp"

int findCloseParentheses(std::vector<std::string> &inputs, int start) 
{
    int ignore = 0;
    for (int i = start + 1; static_cast<unsigned long>(i) < inputs.size(); ++i) 
    {
        if (inputs.at(i) == "(") 
	{
            ++ignore;
        }
        if (inputs.at(i) == ")") 
	{
            if (ignore == 0) 
	    {
                return i;
            } 
	    else 
	    {
                --ignore;
            }
        }
    }

    return -1; //prevent compiler warning
}

Base* nightmare(std::vector<std::string> &inputs) 
{
    Base* connect = nullptr; //this is where the NIGHTMARE begins

    for (int i = 0; static_cast<unsigned long>(i) < inputs.size(); ++i) 
    {
	//if there are no connectors yet, we must create two new exe's instead of one once we find the first connector 
	if (connect == nullptr) 
	{ 
	    Base* exeLeft = nullptr;
	    Base* exeRight = nullptr;
	    bool parenthesis = false;

	    //check if the first statement is in parenthesis
	    if (inputs.at(0) == "(") 
	    {
		std::vector<std::string> parenInputs;
		for (int j = 1; j < findCloseParentheses(inputs, 0); ++j) 
		{
		    parenInputs.push_back(inputs.at(j));
		}
		exeLeft = nightmare(parenInputs);

		i = findCloseParentheses(inputs, i) + 1;
	    }

	    if (static_cast<unsigned long>(i) <= inputs.size() -1) 
	    {
		//for the first connector we find, create subvectors of the commands on its left and right so we can create an Exe from each command
		if (inputs.at(i) == ";" || inputs.at(i) == "&&" || inputs.at(i) == "||" || inputs.at(i) == "|") 
		{
		    if (exeLeft == nullptr) 
		    {
			std::vector<std::string> subInputLeft;
			for (int j = 0; j < i; ++j) 
			{
			    subInputLeft.push_back(inputs.at(j));
			}
			exeLeft = new Exe(subInputLeft);
		    }

		    int h = i + 1;
		    std::string space = " ";
		    //h should be at the next connector at the end of this for loop
		    while (inputs.at(h) != ";" && inputs.at(h) != "||" && inputs.at(h) != "&&" && inputs.at(h) != space && inputs.at(h) != "|" && static_cast<unsigned long>(h) < inputs.size() - 1) 
		    { 
			++h;
		    }

		    if (inputs.at(i + 1) == "(") 
		    {
			std::vector<std::string> parenInputs;
			for (int j = i + 2; j < findCloseParentheses(inputs, i + 1); ++j) 
			{
			    parenInputs.push_back(inputs.at(j));
			}
			//recursively generate trees for nested commands
			exeRight = nightmare(parenInputs);
			parenthesis = true;
		    }

		    if (exeRight == nullptr) 
		    {
			//add strings from z, which is one next to i, which is the current connector, to h (the next connector)
			std::vector<std::string> subInputRight; 
			for (int z = i + 1; z < h; ++z) 
			{
			    subInputRight.push_back(inputs.at(z));
			}

			//if h did not find another connector, it means that the rest of the inputs should be the cmdlist for the connector
			if (static_cast<unsigned long>(h) == inputs.size() - 1) 
			{ 
			    subInputRight.push_back(inputs.at(inputs.size() - 1));
			}
			exeRight = new Exe(subInputRight);
		    }

		    if (inputs.at(i) == ";") 
		    {
			connect = new ConnectorSemicolon(exeLeft, exeRight);
		    }
		    else if (inputs.at(i) == "&&") 
		    {
			connect = new ConnectorAnd(exeLeft, exeRight);
		    }
		    else if (inputs.at(i) == "||") 
		    {
			connect = new ConnectorOr(exeLeft, exeRight);
		    }
		    else if (inputs.at(i) == "|") {
			connect = new ConnectorPipe(exeLeft, exeRight);
		    }

		    if (parenthesis) 
		    {
			if (static_cast<unsigned long>(findCloseParentheses(inputs, i + 1)) == inputs.size() - 1) 
			{
			    i = inputs.size();
			} 
			else 
			{
			    i = findCloseParentheses(inputs, i + 1);
			}
		    } 
		    else 
		    {
			//if h is the last input then stop the for loop
			if (static_cast<unsigned long>(h) == inputs.size() - 1) 
			{ 
			    i = inputs.size();
			}
			else 
			{
			    //if h is at the connector, subtract one because at the end of the for loop i will get added one (++i), leaving it at the next connector spot during the next loop
			    i = h - 1; 
			}
		    }
		}
	    }
	    else 
	    {
		connect = exeLeft;
	    }
	} 
	else //if there is a connector already, further connectors have to be connected to it instead of making two new exe objects
	{ 
	    Base* exeRight = nullptr;
	    bool parenthesis = false;

	    //all of this is basically the same as the if statement above except now there is connector that is not null
	    std::string space = " ";
	    int v = i + 1;

	    while (inputs.at(v) != ";" && inputs.at(v) != "||" && inputs.at(v) != "&&" && inputs.at(v) != space && inputs.at(v) != "|" && static_cast<unsigned long>(v) < inputs.size() - 1) 
	    {
		++v;
	    }

	    if (inputs.at(i + 1) == "(") 
	    {
		std::vector<std::string> parenInputs;
		for (int j = i + 2; j < findCloseParentheses(inputs, i + 1); ++j) 
		{
		    parenInputs.push_back(inputs.at(j));
		}
		//recursively generate trees for nested commands
		exeRight = nightmare(parenInputs);
		parenthesis = true;
	    }

	    if (exeRight == nullptr) 
	    {
		//add strings from z, which is one next to i, which is the current connector, to h (the next connector)
		std::vector<std::string> subInputRight; 
		for (int z = i + 1; z < v; ++z) 
		{
		    subInputRight.push_back(inputs.at(z));
		}

		//if h did not find another connector, it means that the rest of the inputs should be the cmdlist for the connector
		if (static_cast<unsigned long>(v) == inputs.size() - 1) 
		{ 
		    subInputRight.push_back(inputs.at(inputs.size() - 1));
		}
		exeRight = new Exe(subInputRight);
	    }

	    if (inputs.at(i) == ";") 
	    {
		connect = new ConnectorSemicolon(connect, exeRight);
	    }
	    else if (inputs.at(i) == "&&") 
	    {
		connect = new ConnectorAnd(connect, exeRight);
	    }
	    else if (inputs.at(i) == "||") 
	    {
		connect = new ConnectorOr(connect, exeRight);
	    }
	    else if (inputs.at(i) == "|") 
	    {
		connect = new ConnectorPipe(connect, exeRight);
	    }

	    if (parenthesis) 
	    {
		if (static_cast<unsigned long>(findCloseParentheses(inputs, i + 1)) == inputs.size() - 1) 
		{
		    i = inputs.size();
		} 
		else 
		{
		    i = findCloseParentheses(inputs, i + 1);
		}
	    } 
	    else 
	    {
		if (static_cast<unsigned long>(v) == inputs.size() - 1) //if h is the last input then stop the for loop
		{ 
		    i = inputs.size();
		}
		else 
		{
		    //if h is at the connector, subtract one because at the end of the for loop i will get added one (++i), leaving it at the next connector spot during the next loop
		    i = v - 1; 
		}
	    }
	}
    }
    //now return the tree
    //but first check to see if only one command was input with no connectors and handles it if so
    if (connect == nullptr) 
    { 
	std::vector<std::string> oneCommand;
	for (int i = 0; static_cast<unsigned long>(i) < inputs.size(); ++i) 
	{
	    oneCommand.push_back(inputs.at(i));
	}

	Base *exe = new Exe(oneCommand);
	return exe;
    } 
    else 
    {
	return connect;
    }
}

