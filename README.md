# CS 100 RSHELL
Winter Quarter 2019
Melanie Aguilar, SID: 862033156
Surya Singh, SID: 862033627

## Introduction
Create a shell that can (1) print a command prompt, (2) read in a line of commands from standard input, and (3) Execute commands using fork, execvp and waitpid. The command prompt should be able to print a line containing “$” in order to execute and run commands inputted by the user. The prompt should be able to read the line of commands and determine which command the user is referring to and execute in a specific manner.  Execvp command will be used to run the executable from one of the PATH environment variable  locations. In this assignment,we used a composite pattern, which helps in partitioning a group of objects. The inputs are taken in from the user, then through the fork(), execvp(), wait(), we are going to run and execute the commands based on connectors. 

### Diagram
![GitHub Logo](/images/uml.png)

#### Classes
BASE CLASS:

Command.h: This is that abstract base class that contains virtual functions inherited by the child classes

Class: SingleCommand: This class should use Parse() to read in the input from the user and divide the entire input into single/individual strings. It should then check that each string is valid and also check if the string could be a comment inputted by the user(starting with “#”).

Class Multiple Commands: This class does the same as the the SingleCommand class except it accounts for multiple arguments that the user has inputted. This class will be used to construct and join the classes: “Semi”, “And”, and “Or” (these are the connectors). If Parse() detects a connector, then it will go to the class that correspond to that connector and then determine how the commands will be executed.

Class: Semi: This class runs with the properties of a semi colon input which says the second command executes no matter the outcome of the first command.

Class: Or: This class runs with the properties of the “||” input. With this type of connector we will have to utilize the forking method to check if the second argument is able to pass (according to the truth/false value of the preceding argument).

Class: And: This class runs with the properties of the “&&” input. If the command input before the && executes successfully then the command argument after the && also executes but if the command before the && fails, the command after the && does not get executed.

Class Exit: This class will be used to exit out of the commandprompt when the user exits and account for all things that should be taken into account when exiting such as what things to save, as well as what things to destory.

##### Prototypes/Research
```c++
    #include <iostream>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>


    using namespace std;


    int main(){

        char* cmd = "ls";
        char *argv[2];
        argv[0] = "ls";
        argv[1] = NULL;
        pid_t parent = getpid();
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
             execvp(cmd, argv);
             return 0;
         }
    }
```
