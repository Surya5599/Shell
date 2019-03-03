#include <iostream>
#include "pareCommands.h"
#include <queue>
using namespace std;

pareCommands::pareCommands(string data) {
    this->data = data;
}


void pareCommands::Parse() {
    if(countParenthesis(data) % 2 == 1){
        wrongParenthesis = true;
        return;
    }
    int hash = -1;
        hash = data.find('#');
        if(hash > -1){
            if(!findQuotes(hash, 0)){
                data.erase(data.begin() + hash, data.end());
            }
        }
    int newBegin = 0;
    string foundCmd;
    for(unsigned i = 0; i < data.size(); ++i) {
            if(data[i] == ';'){
                if(findParenthesis(i, newBegin) == true){
                    int x = findConnectors(i + 1, newBegin);
                    if(x != -1){
                        foundCmd = data.substr(newBegin, x - newBegin);
                        i = x + 2;
                        newBegin = i;
                        commandQueue.push(foundCmd);
                    }
                }
                else{
                    foundCmd = data.substr(newBegin, i - newBegin);
                    if(foundCmd[0] == ' '){
                        foundCmd = data.substr(newBegin + 1, i - newBegin - 1);
                    }
                    newBegin = i + 2;
                    commandQueue.push(foundCmd);
                    connectors.push_back(";");
                }
            }
            else if(data[i] == '&' && data[i+1] == '&') {
                 if(findParenthesis(i, newBegin) == true){
                    int x = findConnectors(i + 1, newBegin);
                    if(x != -1){
                        foundCmd = data.substr(newBegin, x - newBegin);
                        if(foundCmd[0] == ' '){
                            foundCmd = data.substr(newBegin + 1, x - newBegin - 1);
                        }
                        i = x + 1;
                        newBegin = i + 1;
                        commandQueue.push(foundCmd);
                    }
                }
                else{
                    foundCmd = data.substr(newBegin, i - newBegin);
                    if(foundCmd[0] == ' '){
                        foundCmd = data.substr(newBegin + 1, i - newBegin - 1);
                    }
                    newBegin = i + 3;
                    commandQueue.push(foundCmd);
                    connectors.push_back("&&");
                }
            }
            else if(data[i] == '|' && data[i+1] == '|') {
                 if(findParenthesis(i, newBegin) == true){
                    int x = findConnectors(i + 1, newBegin);
                    if(x != -1){
                        foundCmd = data.substr(newBegin, x - newBegin);
                        if(foundCmd[0] == ' '){
                            foundCmd = data.substr(newBegin + 1, x - newBegin - 1);
                        }
                        i = x + 1;
                        newBegin = i + 1;
                        commandQueue.push(foundCmd);
                    }
                }
                else{
                    foundCmd = data.substr(newBegin, i - newBegin);
                    if(foundCmd[0] == ' '){
                        foundCmd = data.substr(newBegin + 1, i - newBegin - 1);
                    }
                    newBegin = i + 3;
                    commandQueue.push(foundCmd);
                    connectors.push_back("||");
                }
            }
            
        }
    foundCmd = data.substr(newBegin, data.size());
    if(foundCmd[0] == ' '){
        foundCmd = data.substr(newBegin + 1, data.size());
    }
    if(foundCmd.size() > 1) {
        commandQueue.push(foundCmd);
    }
    else{
        connectors.pop_back();
    }
    readyForExecution();
}

bool pareCommands::runCommand() {
        if(wrongParenthesis == true){
            cout << "Syntax Error: Parenthesis Missing" << endl;
            return false;
        }
        if(multCommand.size() != 0){
            int j = 0;
            bool lastRun;
            if(multCommand.size() == connectors.size()){
                if(connectors.at(0) == "&&" || connectors.at(0) == ";"){
                    lastRun = multCommand.at(j)->runCommand();
                    connectors.erase(connectors.begin());
                }
                else{
                    return true;
                }        
            }
            else{
                lastRun = multCommand.at(j)->runCommand();
            }
            if(lastRun > 1){
                lastRun = false;
            }
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
}

bool pareCommands::findParenthesis(int loc, int newBegin) {
    int rightPare = 0;
    int firstPos = -1;
    int secPos = -1;
        for(unsigned i = newBegin; i < data.size(); ++i) {
            if(data[i] == '('){
                if(rightPare == 0){
                    firstPos = i;
                }
                ++ rightPare;
            }
            if(data[i] == ')'){
                --rightPare;
                if(rightPare == 0){
                    secPos = i;
                    break;
                }
            }
        }
        if(loc > firstPos && loc < secPos){
            return true;
        }
    return false;
}

int pareCommands::findConnectors(int loc, int newBegin) {
        for(unsigned i = loc; i < data.size(); ++i) {
            if(data[i] == ';') {
                if(findParenthesis(i, newBegin) == false && findQuotes(i, newBegin) == false){
                    connectors.push_back(";");
                    return i;
                }
            }
            if(data[i] == '&' && data[i+1] == '&') {
                if(findParenthesis(i, newBegin) == false && findQuotes(i, newBegin) == false){
                    connectors.push_back("&&");
                    return i;
                }
            } 
            if(data[i] == '|' && data[i+1] == '|') {
                if(findParenthesis(i, newBegin) == false && findQuotes(i, newBegin) == false){
                    connectors.push_back("||");
                    return i;
                }
            }
        }
        return -1;
    }
    
    bool pareCommands::findQuotes(int loc, int newBegin){
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
    
    void pareCommands::readyForExecution(){
        string cmd;
        int ctr; 
        ctr = -1;
        while(!commandQueue.empty()){
            cmd = commandQueue.front();;
            ctr = ctr + 1;
            if(checkIfConnectors(cmd) == false){
                int loc = -1;
                loc = cmd.find("exit"); //loc = 19
                if(loc > -1){
                    if(checkQuotes(cmd, loc) == false){
                        cmd.erase(cmd.begin() + loc, cmd.end() - 1); 
                    }
                }
                singleCommand* s1 = new singleCommand(cmd);
                s1->Parse();
                multCommand.push_back(s1);
            }
            else{
                int rightPare = 0;
                int firstPos = -1;
                int secPos = -1;
                for(unsigned i = 0; i < cmd.size(); ++i) {
                    if(cmd[i] == '('){
                        if(rightPare == 0){
                            firstPos = i;
                        }
                        ++ rightPare;
                     }
                    if(cmd[i] == ')'){
                        --rightPare;
                        if(rightPare == 0){
                            secPos = i;
                            break;
                    }
                    }
                }
                cmd = cmd.substr(0 + firstPos + 1, secPos -1);
                int loc = -1;
                loc = cmd.find("exit");
                if(loc > -1){
                    if(checkQuotes(cmd, loc) == false){ 
                        cmd.erase(cmd.begin() + loc, cmd.end());
                    }
                }
                if(ctr == 0 && cmd.size() < 1){
                    if(multCommand.size() > 2){
                        connectors.erase(connectors.begin());
                    }
                }                
                else if(cmd.size() < 2 && ctr > 0){
                    connectors.erase(connectors.begin() + (ctr - 1));
                }
                else{
                    pareCommands* s1 = new pareCommands(cmd);
                    s1->Parse();
                    multCommand.push_back(s1);
                }
            }
            commandQueue.pop();
        }
    }
    
    bool pareCommands::checkQuotes(string cmd, int loc){
        int firstPos = -1;
        int secPos = -1;
        for(unsigned i = 0; i < cmd.size(); ++i) {
            if(cmd[i] == '\"'){
                firstPos = i;
                break;
            }
        }
        for(unsigned j = firstPos + 1; j < cmd.size(); ++j) {
                if(cmd[j] == '\"') {
                    secPos = j;
                    break;
            }
        }
        if(loc > firstPos && loc < secPos){
            return true;
        }
        return false;
    }
    
    bool pareCommands::checkIfConnectors(string userInput){
        bool multiple = false;
        for(unsigned i = 0; i < userInput.size(); ++i) {
                if(userInput[i] == ';' && checkQuotes(userInput, i) == false){
                    multiple = true;
                }
                if(userInput[i] == '|' && userInput[i+1] == '|' && checkQuotes(userInput, i) == false){
                        multiple = true;
                }
                if(userInput[i] == '&' && userInput[i+1] == '&' && checkQuotes(userInput, i) == false) {
                        multiple = true;
                }
            }
        return multiple;
}
int pareCommands::countParenthesis(string userInput){
        int ctr = 0;
        for(int i = 0; i < userInput.size(); ++i){
            if(userInput[i] == ')'){
                ++ctr;
            }
            else if(userInput[i] == '('){
                ++ctr;
            }
        }
        return ctr;
    }
