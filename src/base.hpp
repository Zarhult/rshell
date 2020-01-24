#ifndef __BASE_HPP__
#define __BASE_HPP__

class Base
{
public:
    Base() {};
    virtual ~Base() = default;
    virtual int execute() = 0;
};

#endif // __BASE_HPP__
