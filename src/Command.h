#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <stdio.h>
using namespace std;


class Command{
    protected:
    bool lastRun;
    
    public:
    Command(){};
    virtual bool runCommand() = 0;
    virtual void Parse() = 0;
    
};

#endif
