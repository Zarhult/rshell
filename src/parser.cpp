#include <string>
#include <vector>
#include "base.hpp"
#include "connectoror.hpp"
#include "connectorand.hpp"
#include "connectorsemicolon.hpp"
#include "exe.hpp"

std::vector<std::string> parse(std::string command) {
	std::vector<std::string> inputs; // parse command into a vector of each command element (executables, connectors, quotes, parentheses, etc)
        int startIndex; // beginning of a command element, starting with the very beginning of the input string
        for (int i = 0; static_cast<unsigned long>(i) < command.size(); ++i)
        {
            startIndex = i;

            //stop parsing once a comment appears
            if (command.at(i) == '#')
            {
                break;
            }

            //handle parentheses
            if (command.at(i) == '(')
            {
                inputs.push_back("(");
            }
            else if (command.at(i) == ')')
            {
                inputs.push_back(")");
            }

            //handle quote blocks
            char q = '\"';
            if (command.at(i) == q)
            {
                int temp = i;
                ++i;
                while (command.at(i) != q) //set i to position of closing quote
                {
                    ++i;
                }
                inputs.push_back(command.substr(temp + 1, i - temp - 1)); //push contents of the quote block to inputs vector

                startIndex = i;
            }

            //handle semicolon connector
            if (command.at(i) == ';')
            {
                inputs.push_back(";");
            }

            //handle everything else (ls, mkdir, &&/|| connectors, test, etc)
            if(command.at(i) != '"' && command.at(i) != '(' && command.at(i) != ')' && command.at(i) != ';' && command.at(i) != ' ')
            {
                while(static_cast<unsigned long>(i) < command.size() - 1 && command.at(i + 1) != '"' && command.at(i + 1) != '(' && command.at(i + 1) != ')' && command.at(i + 1) != ';' && command.at(i + 1) != ' ') //set i to index of end of command, which precedes either a space, semicolon, or paren (or stop at the end of the command if reached)
                {
                    ++i;
                }
                while (static_cast<unsigned long>(i) < command.size() - 2 && command.at(i + 2) == ' ') //get rid of any possible extra spaces
                {
                    command.erase(i + 2, 1);
                }
		std::string input = command.substr(startIndex, i - startIndex + 1 + (static_cast<unsigned long>(i) == command.size() - 1)); //(i == command.size() - 1) conditional accounts for case where we are at the command's end, and i is one less than it would be if it reached the character after the command element
                inputs.push_back(input);

                startIndex = i;
            }
        }

        return inputs;
}

