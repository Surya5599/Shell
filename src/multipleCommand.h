#ifndef _MULTIPLECOMMAND_H_
#define _MULTIPLECOMMAND_H_

#include "Command.h"
#include "singleCommand.h"
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
    bool findQuotes(int loc, int newBegin);
    int findConnectors(int loc, int newBegin);
    
    public:
    multipleCommand(string data);
    void Parse();
    bool runCommand();

    
};

#endif
