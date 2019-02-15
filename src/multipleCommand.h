#ifndef _MULTIPLECOMMAND_H_
#define _MULTIPLECOMMAND_H_

#include "Command.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class multipleCommand:public Command {
    private:
    string data;
    vector<Command* > multCommand;
    vector<string> connectors;
    
    
    
    public:
    multipleCommand(string data);
    void Parse();
    bool runCommand();
    bool findQuotes(int loc);
    int findConnectors(int loc);
    
};

#endif
