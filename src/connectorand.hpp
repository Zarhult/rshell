#ifndef __CONNECTORAND_HPP__
#define __CONNECTORAND_HPP__

#include "base.hpp"

class ConnectorAnd : public Base
{
private:
    Base *LeftExec;
    Base *RightExec;

public:
    ConnectorAnd(Base *left, Base *right);

    virtual int execute();
};

#endif // __CONNECTORAND_HPP__
