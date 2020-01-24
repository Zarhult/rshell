#ifndef __TEST_HPP__
#define __TEST_HPP__

#include <vector>
#include <string>
#include "base.hpp"

class Test : public Base
{
    private:
	std::vector<std::string> cmd;

    public:
	Test(std::vector<std::string> input);

	virtual int execute();
};

#endif // __TEST_HPP__
