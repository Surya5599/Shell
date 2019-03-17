# CS 100 RSHELL
Winter Quarter 2019
Melanie Aguilar, SID: 862033156
Surya Singh, SID: 862033627

## Introduction
Create a shell that can (1) print a command prompt, (2) read in a line of commands from standard input, and (3) Execute commands using fork, execvp and waitpid. The command prompt should be able to print a line containing “$” in order to execute and run commands inputted by the user. The prompt should be able to read the line of commands and determine which command the user is referring to and execute in a specific manner.  Execvp command will be used to run the executable from one of the PATH environment variable  locations. In this assignment,we used a composite pattern, which helps in partitioning a group of objects. The inputs are taken in from the user, then through the fork(), execvp(), wait(), we are going to run and execute the commands based on connectors. 

## Diagram // UPDATED
![GitHub Logo](/images/uml.png)

## Classes // UPDATED
BASE CLASS:
Command.h: This is that abstract base class that contains virtual functions inherited by the child classes contains three virtual functions inherited but both children class

Class: SingleCommand: This class stores the user input as a member variable: string data using a constructor. The Parse() function in this class, looks at that data and checks for the outliers for example, does it have ("#") if it does it checks if the ("#") is within quotes if it is not, it removes everything from the # because all that is considered commencted command. Then it takes the data, and parses it with a deliminator (" ")*space* and stores each word in a vector of strings which is a private member variable. Once that is done, the runCommand() function, checks if the vector has something, if it does it stores those strings into char* based on the excevp inputs and populates the argv[] used by excevp and runs the command.

Class: Multiple Commands: This class is called when there is a connector in a string, that means this is a multipleCommand; multiple Command's Parse() function does the same thing for # first then continues on to create objects of singleCommand by parsing each command based on connectors and pushes them into private member variable multCommand which hold reference to the Command the abstract base class. This class also has private memeber variable of strings which holds the connectors in the order they are inputted. Once the runCommand for this class is called. This class runs calls runCommand on every singleCommand object based on the connectors.

Class: Parenthesis Commands: This class creates an object for a parenthesis command which in turn works like multiple command but the parenthesis create a sort of precedence that this class accounts for in order to run the commands. It does so but creating objects of single commands and multiple commands in order to run the precedence. 

Class: Symbols Commands: This class extends our rshell program so that it properly handles input redirection <, output redirection > and >>, and piping |. To do so, we utilized the functions dup(), dup2(), and pipe(). while using these we used a file decriptor so that we can read and/or write into existing files. If the files do not exits, we make sure to handle the case properly by either creating a new file or sending an error message. We also send error messages for invalid commands, as well as setiing flags in every command so that we know what symbols we need to operate with.

## Prototypes/Research
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

Fork(): this is used to create new processes called child processes which runs parallel to the parent process, and is exactly the same. However anything modified in the child process is not modified in the parent process. The fork() returns a process id (-1 if fork is unsuccessful, 0 if the process is a child process, and positive number >0 if the process is a parent process).

int execvp(const char *file, char *const argv[]): this function takes in a constant character type pointer which points to the filename associated with the file being executed. The array of pointers must be terminated by a NULL pointer. This function is used to replace the current process with a new process while the first process still runs, allowing it to run multiple program to be executed at once.

pid_t waitpid(pid_t pid, int *status, int options): this function takes in the inputs of the pid_t which is the code returned by fork, the status which is returned from the status of the child, the int options variable. The waitpid call is used in the parent processes, and it suspends the parent processes/execvp or rather keeps it in waiting mode,  until the child execvp is completed and executed.

The prototype above includes the execution of three functions and runs the command "ls" which shows the files in the current folder, the prototye functions shows the use of wait in the parent process as the waitpid is used if the current pid is parent, which should wait for child process to execute and finish executing. Waitpid helps avoid child zombies and allow for destruction of the child process before parent can execute.

pipe(): Has 2 parts. One part is for writing and another is used for reading. a[1] (an array called "a") is used for writing and a[0] for reading. After reading from pipe, program will show output on console. 

dup(): The dup() system call creates a copy of a file descriptor. Uses the LOWEST-NUMBERED unused descriptor for the new descriptor. If copy is successfully created, then the original and copy file descriptors may be used interchangeably.

dup2(): The dup2() system call is similar to dup(), but it uses the descriptor number SPECIFIED by the user.

fd: Will contain the values: -1, 0, 1, 2. A -1 means: ERROR! FAILED!!. 0 means: read from stdin => read from fd 0 (Input from the keyboard). 1 means: write to stdout => write to fd 1 (Output to the console). 2 means: write to stderr => write to fd 2.

## Development and Testing RoadMap //UPDATED
Order of design:

Main.cpp (main(), print Prompt(), singleExecute, multipleExecute, checkIfSingle) 

Command( virtual runCommand(),Virtual Parse(),Virtual findQuotes(int) ,Virtual runCommand())

SingleCommand. (Parse(), findQuotes(int) , runCommand())

MultipleCommand (Parse(), findQuotes(int) , runCommand())

ParenthesisCommand(Parse(), runCommand())
Unit_test.cpp: create extensive testing for singleCommands, MultipleCommands, CommentedCommands, ExitCommands, PrecedenceCommands, TestCommands, SymbolicTestCommands.
singleCommands testing: Includes testing of basic commands such as echo, ls , mkdir, and even an invalid command
multipleCommand testing: Includes testing of connectors and how they work together and sometimes not work together.
CommentedCommands testing: Includes testing what happens to commands that have comments in middle, beginning or end
Exit Commands: testing on exit is hard for google test as, once exit is called it exits the googletest therefore, not continuing with any testing after so much more exit testing will be done in bash integration testing
PrecedenceCommands: Includes testing of basic commands mentioned above but this time with precedence and tests if the code can handle these commands
TestCommands and Symbolic Commands: This is its own testing command which returns true or false based on if a path exists that the user is trying to see.


./test will run the unit_tests....if the failing tests are being due to ls, that probably because of an extra directory being created please disregard those errors.

Integration tests include many edge cases for single, multiple, commented,exit commands, precedence, testcommands, and symbolictests.

Division: //Updated

All files were worked on collabratively, by both Melanie Aguilar and Surya

## Challanges Faced and how we solved them //Update
Challenge one: A problem that occured was that during unit_testing we had to somehow look at the printed outcome of the command being ran, as this was not taught of how to use google test, after some intense research. 
Using this source https://stackoverflow.com/questions/3803465/how-to-capture-stdout-stderr-with-googletest/33186201
it was clear as to how we can store a stdout into a string in order to compare to expected output. From this we learned the features of google test and how we can use them in order to create more advanced and elaborative testing.

Challenge two: Another problem we faced was creating an exit command, as we discovered a bug that exit was not working when there was a command that was invalid executed before it. For example if the user enter a command thats invalid for example "dog" then the code tells them that the command is invalid, then if they enter exit, nothing would happen and it would allow users to enter something again but if exit was entered this second time, it exits! So the bug we discovered was that the code wasn't exiting the child process, after some research we learned that the child only returns back if the command is not found by excevp but if it is it never returns, meaning the child process was returning but it was never getting destroyed and was becoming a zombie process. After making a few edits, we were able to overcome this problem and in return learned something new.


