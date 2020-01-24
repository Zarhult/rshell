#ifndef __CONNECTORSEMICOLON_HPP__
#define __CONNECTORSEMICOLON_HPP__

#include "base.hpp"

class ConnectorSemicolon : public Base
{
private:
	Base* LeftExec;
	Base* RightExec;

public:
	ConnectorSemicolon(Base* left, Base* right);

	virtual int execute();
};

#endif // __CONNECTORSEMICOLON_HPP__
