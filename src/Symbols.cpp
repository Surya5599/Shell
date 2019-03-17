#include "Symbols.h"

using namespace std;

Symbols::Symbols(vector<string>sym) {
    this->sym = sym;
}

void Symbols::Parse() {
    int j = 0;
    int lastloc = 0;
    int newBegin = 0;
    bool done = false;
    while(!done){
        int loc = 0;
        for(int i = newBegin; i < sym.size(); ++i) {
            if(sym.at(i) == "|") {
                loc = i;
                newBegin = loc + 1;
                break;
            }
            if(i == sym.size()-1){
                done = true;
            }
        }
        if(loc != 0){
            vector<string> v1;
            for(int k = lastloc; k < loc; ++k){
                v1.push_back(sym.at(k));
            }
            masterVector.push_back(v1);
            lastloc = loc + 1;
        }
    }
    vector<string> v1;
    for(int i = newBegin; i < sym.size(); ++i){
        v1.push_back(sym.at(i));
    }
    masterVector.push_back(v1);
}

bool Symbols::runCommand() {
    for(int j = 0; j < masterVector.size(); ++j){
            vector<string> commands = masterVector.at(j);
            int loc = 0;
            for(int i = 0 ; i < commands.size(); ++i){
                if(commands.at(i) == "<"){ // input
                    loc = i;
                    files.push_back(commands.at(loc + 1));
                    if(loc + 2 < commands.size()){
                        for(int k = loc + 1; k < commands.size(); ++k){
                            if(commands.at(k) == ">>"){
                                flags.push_back("doubleinputoutput");
                                files2.push_back(commands.at(k + 1));
                            }
                            else if(commands.at(k) == ">"){
                                flags.push_back("inputoutput");
                                files2.push_back(commands.at(k + 1));
                            }
                            else if(commands.at(k) == "<"){
                                flags.push_back("input");
                                files.pop_back();
                                files.push_back(commands.at(k+1));
                            }
                        }
                    }
                    else{
                        flags.push_back("input");
                    }
                    break;
                }
                if(commands.at(i) == ">>"){ // output + append
                    loc = i;
                    flags.push_back("doubleoutput");
                    files.push_back(commands.at(loc + 1));
                    break;
                }
                if(commands.at(i) == ">"){ // output
                    loc = i;
                    flags.push_back("output");
                    files.push_back(commands.at(loc + 1));
                    break;
                }
            }
            if(loc == 0){
                flags.push_back("none");
                loc = commands.size();
                files.push_back("none");
            }
            else{
                int size = masterVector.at(j).size();
                masterVector.at(j).erase(masterVector.at(j).begin() + loc, masterVector.at(j).end());
            }
        
}
    execute();
}

bool Symbols::execute(){
     bool run = true;
    int inputlist[flags.size()];
    int outputlist[flags.size()];
    int in = 0;
    int out = 0;
    for(int i = 0; i < flags.size(); ++i){
        if(flags.at(i) == "input"){
            string inputfile = files.at(i);
            in = open(inputfile.c_str(), O_RDONLY, S_IRWXU);
               if(in == -1){
                   perror("File doesn't exist");
                   return false;
               }
            inputlist[i] = in;
            outputlist[i] = -1;
        }
        else if(flags.at(i) == "inputoutput"){
            string inputfile = files.at(i);
            in = open(inputfile.c_str(), O_RDONLY, S_IRWXU);
            string outputfile = files2.at(i);
            out = open(outputfile.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
            inputlist[i] = in;
            outputlist[i] = out;
        }
        if(flags.at(i) == "doubleinputoutput"){
            string inputfile = files.at(i);
            in = open(inputfile.c_str(), O_RDONLY, S_IRWXU);
            string outputfile = files2.at(i);
            out = open(outputfile.c_str(), O_RDWR | O_CREAT | O_APPEND , S_IRWXU);
            inputlist[i] = in;
            outputlist[i] = out;
        }
        else if(flags.at(i) == "output"){
            string outputfile = files.at(i);
            out = open(outputfile.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
            inputlist[i] = -1;
            outputlist[i] = out;
        }
        else if(flags.at(i) == "doubleoutput"){
            string outputfile = files.at(i);
            out = open(outputfile.c_str(), O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
            inputlist[i] = -1;
            outputlist[i] = out;
        }
        else if(flags.at(i) == "none"){
            inputlist[i] = -1;
            outputlist[i] = -1;
        }
    }
    
    
    for(int i = 0; i < flags.size() -1 ; i++){
        int p[2];
        pipe(p);
        inputlist[i + 1] = p[0];
        outputlist[i] = p[1];
    }
    
    for(int  k = 0; k < masterVector.size(); ++k){
       
        int status;
        pid_t pid;
        pid = fork();
        
        
        if (pid == -1) {
            perror("Fork Error");
        }
        
        else if(pid == 0){
                vector<string> commands = masterVector.at(k);
                char *cmd = &commands.at(0)[0];
                char *argv[commands.size() + 1];
                for(unsigned j = 0; j < commands.size(); ++j){
                    argv[j] = &commands.at(j)[0];
                }
                argv[commands.size()] = NULL;
                if(outputlist[k] != -1){
                    close(1);
                    dup2(outputlist[k], 1);
                }
                if(inputlist[k] != -1){
                    close(0);
                    dup2(inputlist[k], 0);
                }
                if(-1 == execvp(cmd, argv)){
                    perror("Command not found");
                    run = false;
                    _exit(-1);
                }
            }
        else{  //parent
            waitpid(pid, &status, 0);
            if(status > 0){
                run = false;
            }
            if(status == 0){
                run = true;
            }
            close(outputlist[k]);
            if(k > 0){
                close(inputlist[k]);
            }
        }  
    }
    return run;
}
