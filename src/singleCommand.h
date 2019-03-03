#ifndef _SINGLECOMMAND_H_
#define _SINGLECOMMAND_H_

#include "Command.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class singleCommand:public Command {
    private:
    string data;
    vector<string> commands;
    bool findQuotes(int);
    char checkFlag(char* test);
    int runTest(char , char* );
    
    public:
    singleCommand(string data);
    void Parse();
    bool runCommand();
    
    
};

#endif
