#include "singleCommand.h"
#include <bits/stdc++.h> 
#include <cstdlib>
using namespace std;

    singleCommand::singleCommand(string data){
        this->data = data;
    }
    void singleCommand::Parse(){
        int hash = -1;
        hash = data.find('#');
        if(hash > -1){
            data.erase(data.begin() + hash, data.end());
        }
        string sr1;
        string sr2;
        int x = -1;
        x = data.find('\"');
        if(x > -1 && x < data.size()){
            data.erase(remove(data.begin(), data.end(), '\"'), data.end());
        }
        
        istringstream iss(data);
        string parse;
        while(getline(iss, parse, ' ')){
            commands.push_back(parse);
        }
    }
    
    bool singleCommand::runCommand(){
        if(commands.at(0) == "exit"){
                exit(0);
        }
        char *cmd = &commands.at(0)[0];
        char *argv[commands.size() + 1];
        for(unsigned i = 0; i < commands.size(); ++i){
            argv[i] = &commands.at(i)[0];
        }
        argv[commands.size()] = NULL;
        pid_t pid = fork();
        
        if (pid == -1)
        {
            cout << "Fork ERROR" << endl;
        }   
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
            
        }  
        else
        {
            if(-1 == execvp(cmd, argv)){
                    perror("Command Not found");
                    return false;
            }
         }
         return true;
    }
