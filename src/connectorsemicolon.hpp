#ifndef __CONNECTORSEMICOLON_HPP__
#define __CONNECTORSEMICOLON_HPP__

#include <iostream>
#include "base.hpp"

class ConnectorSemicolon : public Base
{
private:
	Base *LeftExec;
	Base *RightExec;

public:
	ConnectorSemicolon(Base *left, Base *right) : LeftExec(left), RightExec(right){};

	virtual int execute()
	{
		bool part1 = false;
		bool part2 = false;
		int test = LeftExec->execute();
		if (test == 0)
		{
			part1 = true;
		}

		int test2 = RightExec->execute();
		if (test2 == 0)
		{
			part2 = true;
		}

		if (part1 || part2)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
};

#endif
