#ifndef _SINGLECOMMAND_H_
#define _SINGLECOMMAND_H_

#include "Command.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class singleCommand:public Command {
    protected:
    string data;
    vector<string> commands;
  
    
    public:
    singleCommand(string data);
    void Parse();
    bool runCommand();
    
};

#endif
