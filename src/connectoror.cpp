#include "connectoror.hpp"

ConnectorOr::ConnectorOr(Base *left, Base *right) : LeftExec(left), RightExec(right) {}

int ConnectorOr::execute()
{
    bool part1 = false;
    bool part2 = false;
    int test1 = LeftExec->execute();
    if (test1 == 0)
    {
	part1 = true;
    }
    else
    {
	int test2 = RightExec->execute();
	if (test2 == 0)
	{
	    part2 = true;
	}
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

