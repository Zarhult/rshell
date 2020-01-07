#ifndef __CONNECTORAND_HPP__
#define __CONNECTORAND_HPP__

#include "base.hpp"

using namespace std;

class ConnectorAnd : public Base
{
private:
    Base *LeftExec;
    Base *RightExec;

public:
    ConnectorAnd(Base *left, Base *right) : LeftExec(left), RightExec(right){};

    virtual int execute()
    {
        bool part1 = false;
        bool part2 = false;
        int test1 = LeftExec->execute();
        if (test1 == 0)
        {
            part1 = true;
            int test2 = RightExec->execute();
            if (test2 == 0)
            {
                part2 = true;
            }
        }

        if (part1 && part2)
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
