#include <iostream>
#include <vector>

int main() {
    std::cout << "$ "; //take in a command
    std::string command;
    getline(std::cin, command);

    std::vector<std::string> inputs; //parse command into a vector of each command element (executables, connectors, etc)
    int startIndex = 0; //beginning of a command element, starting with the very beginning

    for (int i = 0; i < command.size(); ++i) {
        if (command.at(i) == ' ' || i + 1 == command.size()) { //if at the end of a command element...
            while (i + 1 != command.size() && command.at(i + 1) == ' ') { //get rid of any extra spaces there may be
                command.erase(i + 1, 1);
            }
            std::string input = command.substr(startIndex, i - startIndex + (i + 1 == command.size())); //extract command element, separated by spaces
            inputs.push_back(input); //add it to vector of command elements
            startIndex = i + 1;
        }
    }

    std::cout << "Command elements are: " << std::endl;
    for (int i = 0; i < inputs.size(); ++i) {
        std::cout << inputs.at(i);
        std::cout << std::endl;
    }


    int NumOperators = 0;
    for (int i = 0; i < inputs.size(); ++i) {
        if (inputs.at(i) == "||" || inputs.at(i) == "&&" || inputs.at(i) == ";") {
            ++NumOperators;
        }
    }
    std::cout << "Operators: " << NumOperators << std::endl;

    return 0;
}
