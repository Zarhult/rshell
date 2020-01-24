#ifndef __EXE_HPP__
#define __EXE_HPP__

#include <vector>
#include <string>
#include "base.hpp"

class Exe : public Base
{
private:
    std::vector<std::string> cmd;
    bool inputRedirection;
    bool outputRedirection;
    int savedup;
    int newIn;
    int newOut;

public:
    Exe(std::vector<std::string> cmd);
    
    void AppendRedirect(std::vector<std::string> &cmd);
    void InputRedirect(std::vector<std::string> &cmd);
    void OutputRedirect(std::vector<std::string> &cmd);

    void fixInputRedirection();
    void fixOutputRedirection();

    virtual int execute();
};

#endif // __EXE_HPP__
