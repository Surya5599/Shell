#include "singleCommand.h"
#include <bits/stdc++.h> 
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

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
            perror("Fork Error");
        }   
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
            if(status == -1){
                return false;
            }
            if(status == 0){
                return true;
            }
        }  
        else
        {
            if(-1 == execvp(cmd, argv)){
                perror("Command not found");
               _exit(-1);
           }
           _exit(0);
         }
    }
