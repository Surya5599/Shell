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
        int paren = -1;
        paren = data.find('(');
        if(paren > -1){
            if(findQuotes(paren) == false){
                data.erase(remove(data.begin(), data.end(), '('), data.end());
            }
        }
        paren = data.find(')');
        if(paren > -1){
            if(findQuotes(paren) == false){
                data.erase(remove(data.begin(), data.end(), ')'), data.end());
            }
        }
        int hash = -1;
        hash = data.find('#');
        if(hash > -1){
            if(findQuotes(hash) == false){
                data.erase(remove(data.begin(), data.end(), '\"'), data.end());
            }
        }
        if(data == " "){
	        data.erase(data.begin(), data.end());
	    }
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
      if(commands.size() != 0){ 
	    if(commands.at(0) == "exit"){
                exit(0);
        }
        char *cmd = &commands.at(0)[0];
        char *argv[commands.size() + 1];
        for(unsigned i = 0; i < commands.size(); ++i){
            argv[i] = &commands.at(i)[0];
        }
        argv[commands.size()] = NULL;
        if(commands.at(0) == "test" || commands.at(0) == "["){
            char flag = checkFlag(argv[1]);
            int testAnswer = 0;
            if(flag == 'n'){
                testAnswer = runTest(flag, argv[1]);
            }
            else{
                testAnswer = runTest(flag, argv[2]);
            }
            if(testAnswer == 1){
                cout << "(TRUE)" << endl;
                return true;
            }
            else{
                cout << "(FALSE)" << endl;
                return false;
            }
        }
        else{
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
                    lastRun = false;
                    return false;
                }
                if(status == 0){
                    lastRun = false;
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
        }
        return lastRun;
    }
    
    

    bool singleCommand::findQuotes(int loc){
        int firstPos = -1;
        int secPos = -1;
        for(unsigned i = 0; i < data.size(); ++i) {
            if(data[i] == '\"'){
                firstPos = i;
                break;
            }
        }
        for(unsigned j = firstPos; j < data.size(); ++j) {
                if(data[j] == '\"') {
                    secPos = j;
                }
        }
        if(loc > firstPos && loc < secPos){
            return true;
        }
        return false;
    }
    
    char singleCommand::checkFlag(char* test){
            if(test[1] == 'f'){
                return 'f';
            }
            if(test[1] == 'd'){
                return 'd';
            }
            if(test [1] == 'e'){
                return 'e';
            }
        return 'n';
    }
    int singleCommand::runTest(char flag, char* path){
        if(flag == 'e' || flag == 'n'){
            struct stat path_stat;
            stat(path, &path_stat);
            if(S_ISREG(path_stat.st_mode) == 1){
                return 1;
            }
            if(S_ISDIR(path_stat.st_mode) == 1){
                return 1;
            }
        }
        else if(flag == 'f'){
            struct stat path_stat;
            stat(path, &path_stat);
            if(S_ISREG(path_stat.st_mode) == 1){
                return 1;
            }
        }
        else if(flag == 'd'){
            struct stat path_stat;
            stat(path, &path_stat);
            if(S_ISDIR(path_stat.st_mode) == 1){
                return 1;
            }
        }
        return 0;
    }
