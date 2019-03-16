#ifndef SYMBOLS
#define SYMBOLS

#include "Command.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;


class Symbols : public Command {

    private:
        vector<string>sym;
        vector<vector<string> > masterVector;
        vector<string > flags;
        vector<string > files;
        vector<string > files2;
        
    public:
        Symbols(vector<string>);
        void Parse();
        bool runCommand();
        bool execute();
        //void readyForExecution();
        
};
#endif
    

