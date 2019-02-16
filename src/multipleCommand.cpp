#include "multipleCommand.h"
#include <bits/stdc++.h> 
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


    multipleCommand::multipleCommand(string data) {
        this->data = data;
    }
    
    void multipleCommand::Parse(){
        int hash = -1;
        hash = data.find('#');
        if(hash > -1){
            if(!findQuotes(hash)){ 
                data.erase(data.begin() + hash, data.end());
            }
        }
	int newBegin = 0;
        string singleCmd;
        for(unsigned i = 0; i < data.size(); ++i) {
            if(data[i] == ';'){
                if(findQuotes(i) == true){
                    int x =  findConnectors(i+1);
                    if(x != -1){
                        i = x + 1;
                        singleCmd = data.substr(newBegin , i - newBegin-1);
                        newBegin = i + 1;
                        singleCommand* s1 = new singleCommand(singleCmd);
                        s1->Parse();
                        multCommand.push_back(s1);
                    }
                }
                else{
                    singleCmd = data.substr(newBegin, i - newBegin);
                    newBegin = i + 2;
                    connectors.push_back(";");
                    singleCommand* s1 = new singleCommand(singleCmd);
                    s1->Parse();
                    multCommand.push_back(s1);
                }
            }
            else if(data[i] == '|' && data[i+1] == '|') {
                if(findQuotes(i) == true){
                    int x =  findConnectors(i+2);
                    if(x != -1){
                        i = x + 2;
                        singleCmd = data.substr(newBegin , i - newBegin-2);
                        newBegin = i + 1;
                        singleCommand* s1 = new singleCommand(singleCmd);
                        s1->Parse();
                        multCommand.push_back(s1);
                    }
                }
                else{
                    singleCmd = data.substr(newBegin, i - newBegin);
                    newBegin = i + 3;
                    connectors.push_back("||");
                    singleCommand* s1 = new singleCommand(singleCmd);
                    s1->Parse();
                    multCommand.push_back(s1);
                }
            }
            else if(data[i] == '&' && data[i+1] == '&') {
                if(findQuotes(i) == true){
                    int x =  findConnectors(i+2);
                    if(x != -1){
                        i = x + 2;
                        singleCmd = data.substr(newBegin , i - newBegin-2);
                        newBegin = i + 1;
                        singleCommand* s1 = new singleCommand(singleCmd);
                        s1->Parse();
                        multCommand.push_back(s1);
                    }
                }
                else{
                    singleCmd = data.substr(newBegin, i - newBegin);
                    newBegin = i + 3;
                    connectors.push_back("&&");
                    singleCommand* s1 = new singleCommand(singleCmd);
                    s1->Parse();
                    multCommand.push_back(s1);
                }
            }
        }
        singleCmd = data.substr(newBegin, data.size());
        singleCommand* s1 = new singleCommand(singleCmd);
        s1->Parse();
        multCommand.push_back(s1);
    }
    
    int multipleCommand::findConnectors(int loc) {
        for(unsigned i = loc; i < data.size(); ++i) {
            if(data[i] == ';') {
                connectors.push_back(";");
                return i;
            }
            if(data[i] == '&' && data[i+1] == '&') {
                connectors.push_back("&&");
                return i;
            } 
            if(data[i] == '|' && data[i+1] == '|') {
                connectors.push_back("||");
                return i;
            }
        }
        return -1;
    }
    
    bool multipleCommand::findQuotes(int loc){
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
    
    bool multipleCommand::runCommand(){ 
        int j = 0;
        bool lastRun = multCommand.at(j)->runCommand();
        for(int i = 0; i < connectors.size(); ++i){
            if(connectors.at(i) == "&&"){
                if(lastRun == true){
                    j = j + 1;
                    lastRun = multCommand.at(j)->runCommand();
                }
                else{
                    j = j + 1;
                }
            }
            else if(connectors.at(i) == "||"){
                if(lastRun == false){
                    j = j + 1;
                    lastRun = multCommand.at(j)->runCommand();
                }
                else if(lastRun == true) {
                    
                    j = j + 1;
                    
                }
            }
            else if(connectors.at(i) == ";"){
                    j = j + 1;
                    lastRun = multCommand.at(j)->runCommand();
            }
        }
        return true;
    }
