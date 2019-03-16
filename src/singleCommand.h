#ifndef _SINGLECOMMAND_H_
#define _SINGLECOMMAND_H_

#include "Command.h"
#include "Symbols.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <bits/stdc++.h> 
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class singleCommand:public Command {
    private:
    string data;
    vector<string> commands;
    bool findQuotes(int);
    char checkFlag(char* test);
    int runTest(char , char* );
    void checkSymbols();
    bool runSymbols();
    void outputSymb();
    void inputSymb();
    void doubleSymb();
    void pipe();
    bool exists;
    
    public:
    singleCommand(string data);
    void Parse();
    bool runCommand();
    
    
};

#endif
