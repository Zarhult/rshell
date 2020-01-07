#ifndef __CONNECTOROR_HPP__
#define __CONNECTOROR_HPP__

#include <stdlib.h>
#include "base.hpp"

using namespace std;

class ConnectorOr : public Base
{
private:
    Base *LeftExec;
    Base *RightExec;

public:
    ConnectorOr(Base *left, Base *right) : LeftExec(left), RightExec(right){};
    virtual int execute()
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
};

#endif
