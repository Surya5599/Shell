#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "Command.h"
#include "singleCommand.h"
#include "multipleCommand.h"
using namespace std;

string printPrompt(){
    string input;
    cout << "$ ";
    getline(cin, input);

    return input;
} 

void singleExecute(string input) {
    singleCommand* sc1 = new singleCommand(input);
    sc1->Parse();
    sc1->runCommand();
    return;
}

void multipleExecute(string input){
    multipleCommand* mc1 = new multipleCommand(input);
    mc1->Parse();
    mc1->runCommand();
    return;
}

bool checkIfSingle(string data){
        int firstPos;
        int secPos;
        int connCount = 0;
        int conPos;
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
        for(unsigned i = 0; i < data.size(); ++i) {
                if(data[i] == ';'){
                    conPos = i;
                    ++connCount;
                }
                if(data[i] == '|' && data[i+1] == '|'){
                    conPos = i;
                    ++connCount;
                }
                if(data[i] == '&' && data[i+1] == '&') {
                    conPos = i;
                    ++connCount;
                }
        }
        if(connCount > 1){
            return false;
        }
        if(connCount == 1){
            if(conPos > firstPos && conPos < secPos){
                return true;
            }
        }
        return false;
}

int main(){
    string userInput = "";
    bool multiple = false;
    
    
    
    while(userInput != "exit"){
        userInput = printPrompt();
        for(unsigned i = 0; i < userInput.size(); ++i) {
            if(userInput[i] == ';'){
                multiple = true;
            }
            if(userInput[i] == '|' && userInput[i+1] == '|'){
                    multiple = true;
            }
            if(userInput[i] == '&' && userInput[i+1] == '&') {
                    multiple = true;
            }
        }
        
        if(multiple == false){
                singleExecute(userInput);
        }
        else if(checkIfSingle(userInput) == true){
            singleExecute(userInput);
        }
        else{
            multipleExecute(userInput);
        }
   }
    if(userInput == "exit"){
            return 0;
    }
    
    return 0;
}
