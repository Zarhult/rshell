#ifndef __CONNECTORPIPE_HPP__
#define __CONNECTORPIPE_HPP__

#include "base.hpp"

class ConnectorPipe : public Base
{
private:
    Base* LeftExec;
    Base* RightExec;

public:
    ConnectorPipe(Base* left, Base* right);

    virtual int execute();
};

#endif // __CONNECTORPIPE_HPP__
