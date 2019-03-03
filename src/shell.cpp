#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "Command.h"
#include "singleCommand.h"
#include "multipleCommand.h"
#include "pareCommands.h"

using namespace std;

string printPrompt(){
    string input;
    cout << "$ ";
    getline(cin, input);
    return input;
} 

void singleExecute(string input) {
    //cout << "in single" << endl;
    singleCommand* sc1 = new singleCommand(input);
    sc1->Parse();
    sc1->runCommand();
    return;
}

void multipleExecute(string input){
    //cout << "in multiple" << endl;
    multipleCommand* mc1 = new multipleCommand(input);
    mc1->Parse();
    mc1->runCommand();
    return;
}

void parenExecute(string input) {
    //cout << "in parenthesis" << endl;
    pareCommands* pc1 = new pareCommands(input);
    pc1->Parse();
    pc1->runCommand();
    return;
}

bool checkIfSingle(string data){
        int firstPos = 0;
        int secPos = 0;
        int connCount = 0;
        int conPos = 0;
        int connInQuotes = 0;
        for(unsigned i = 0; i < data.size(); ++i) {
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
        for(unsigned i = 0; i < data.size(); ++i) {
                if(data[i] == ';'){
                    conPos = i;
                    ++connCount;
                    if(conPos > firstPos && conPos < secPos){
                        connInQuotes++;
                    }
                }
                if(data[i] == '|' && data[i+1] == '|'){
                    conPos = i;
                    ++connCount;
                    if(conPos > firstPos && conPos < secPos){
                        connInQuotes++;
                    }
                }
                if(data[i] == '&' && data[i+1] == '&') {
                    conPos = i;
                    ++connCount;
                    if(conPos > firstPos && conPos < secPos){
                        connInQuotes++;
                    }
                }
        }
        if(connInQuotes == connCount){
            return true;
        }
        return false;
}

bool checkParethesis(string data) {
        bool parenExist = false;
        int firstPos = -1;
        int secPos = -1;
        for(unsigned i = 0; i < data.size(); ++i){
            if(data[i] == '('){
                parenExist = true;
            }
            if(data[i] == ')'){
                parenExist = true;
            }
        }
        return parenExist;
        // int connCount = 0;
        // int conPos = 0;
        // bool inPare = false;
        // for(unsigned i = 0; i < data.size(); ++i) {
        //         if(data[i] == ';'){
        //             conPos = i;
        //             ++connCount;
        //             if(conPos > firstPos && conPos < secPos){
        //                 inPare = true;
        //             }
        //         }
        //         if(data[i] == '|' && data[i+1] == '|'){
        //             conPos = i;
        //             ++connCount;
        //             if(conPos > firstPos && conPos < secPos){
        //                 inPare = true;
        //             }
        //         }
        //         if(data[i] == '&' && data[i+1] == '&') {
        //             conPos = i;
        //             ++connCount;
        //             if(conPos > firstPos && conPos < secPos){
        //                 inPare = true;
        //             }
        //         }
        // }
        // if(inPare == true && (connCount > 1)){
        //     return true;
        // }
        // return false;
}

bool checkIfMultiple(string userInput){
    bool multiple = false;
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
    return multiple;
}

int main(){
    string userInput = "";
    while(userInput != "exit"){
        userInput = printPrompt();
        if (checkParethesis(userInput) == true){
                parenExecute(userInput);
            
        }
        else if(checkIfSingle(userInput) == true || checkIfMultiple(userInput) == false){
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
