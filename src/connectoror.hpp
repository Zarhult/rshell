#ifndef __CONNECTOROR_HPP__
#define __CONNECTOROR_HPP__

#include "base.hpp"

class ConnectorOr : public Base
{
private:
    Base *LeftExec;
    Base *RightExec;

public:
    ConnectorOr(Base *left, Base *right);

    virtual int execute();
};

#endif // __CONNECTOROR_HPP__
