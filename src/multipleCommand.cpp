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
            if(!findQuotes(hash, 0)){ 
                data.erase(data.begin() + hash, data.end());
            }
        }
        
    	int newBegin = 0;
        string singleCmd = "";
        for(unsigned i = 0; i < data.size(); ++i) {
            if(data[i] == ';'){
                if(findQuotes(i, newBegin) == true){
                    int x =  findConnectors(i+1, newBegin);
                    if(x != -1){
                        i = x + 1;
                        singleCmd = data.substr(newBegin , i - newBegin-1);
                        if(singleCmd[0] == ' '){
                            singleCmd = data.substr(newBegin+1, i - newBegin-1);
                        }
                        newBegin = i + 1;
                        singleCommand* s1 = new singleCommand(singleCmd);
                        s1->Parse();
                        multCommand.push_back(s1);
                    }
                }
                else{
                    singleCmd = data.substr(newBegin, i - newBegin);
                    if(singleCmd[0] == ' '){
                            singleCmd = data.substr(newBegin+1, i - newBegin-1);
                        }
                    newBegin = i + 2;
                    connectors.push_back(";");
                    singleCommand* s1 = new singleCommand(singleCmd);
                    s1->Parse();
                    multCommand.push_back(s1);
                }
            }
            else if(data[i] == '|' && data[i+1] == '|') {
                if(findQuotes(i, newBegin) == true){
                    int x =  findConnectors(i+2, newBegin);
                    if(x != -1){
                        i = x + 1;
                        singleCmd = data.substr(newBegin , i - newBegin-1);
                        if(singleCmd[0] == ' '){
                            singleCmd = data.substr(newBegin+1, i - newBegin-2);
                        }
                        newBegin = i + 1;
                        singleCommand* s1 = new singleCommand(singleCmd);
                        s1->Parse();
                        multCommand.push_back(s1);
                    }
                }
                else{
                    singleCmd = data.substr(newBegin, i - newBegin);
                    if(singleCmd[0] == ' '){
                            singleCmd = data.substr(newBegin+1, i - newBegin-1);
                        }
                    newBegin = i + 3;
                    connectors.push_back("||");
                    singleCommand* s1 = new singleCommand(singleCmd);
                    s1->Parse();
                    multCommand.push_back(s1);
                }      
            }
            else if(data[i] == '&' && data[i+1] == '&') {
                if(findQuotes(i, newBegin) == true){
                    int x =  findConnectors(i+2, newBegin);
                    if(x != -1){
                        i = x + 1;
                        singleCmd = data.substr(newBegin , i - newBegin - 1);
                        if(singleCmd[0] == ' '){
                            singleCmd = data.substr(newBegin+1, i - newBegin-2);
                        }
                        newBegin = i + 1;
                        singleCommand* s1 = new singleCommand(singleCmd);
                        s1->Parse();
                        multCommand.push_back(s1);
                    }
                }
                else{
                    singleCmd = data.substr(newBegin, i - newBegin);
                    if(singleCmd[0] == ' '){
                            singleCmd = data.substr(newBegin+1, i - newBegin-2);
                        }
                    newBegin = i + 3;
                    connectors.push_back("&&");
                    singleCommand* s1 = new singleCommand(singleCmd);
                    s1->Parse();
                    multCommand.push_back(s1);
                }  
                
            }
            
        }
        singleCmd = data.substr(newBegin, data.size());
        if(singleCmd[0] == ' '){
            singleCmd = data.substr(newBegin + 1, data.size());
        }
        singleCommand* s1 = new singleCommand(singleCmd);
        s1->Parse();
        multCommand.push_back(s1);
    }
    
    int multipleCommand::findConnectors(int loc, int newBegin) {
        for(unsigned i = loc; i < data.size(); ++i) {
            if(data[i] == ';') {
                if(findQuotes(i, newBegin) == false){
                    connectors.push_back(";");
                    return i;
                }
            }
            if(data[i] == '&' && data[i+1] == '&') {
                if(findQuotes(i, newBegin) == false){
                    connectors.push_back("&&");
                    return i;
                }
            } 
            if(data[i] == '|' && data[i+1] == '|') {
                if(findQuotes(i, newBegin) == false){
                    connectors.push_back("||");
                    return i;
                }
            }
        }
        return -1;
    }
    
    bool multipleCommand::findQuotes(int loc, int newBegin){
        int firstPos = -1;
        int secPos = -1;
        for(unsigned i = newBegin; i < data.size(); ++i) {
            if(data[i] == '\"'){
                firstPos = i;
                break;
            }
        }
        for(unsigned j = firstPos + 1; j < data.size(); ++j) {
                if(data[j] == '\"') {
                    secPos = j;
                    break;
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
            return lastRun;
    }
