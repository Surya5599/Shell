#ifndef PARECOMMANDS_H
#define PARECOMMANDS_H


#include "Command.h"
#include "singleCommand.h"
#include "multipleCommand.h"
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>


using namespace std;

class pareCommands:public Command {
    private:
    bool wrongParenthesis;
    string data;
    vector<Command* > multCommand;
    vector<string> connectors;
    queue<string > commandQueue;
    bool findParenthesis(int loc, int newBegin);
    int findConnectors(int loc, int newBegin);
    bool findQuotes(int loc, int newBegin);
    bool checkIfConnectors(string userInput);
    int countParenthesis(string userInput);
    void readyForExecution();
    bool checkQuotes(string cmd, int loc);
    
    
    public:
    pareCommands(string data);
    void Parse();
    bool runCommand();
};

#endif
