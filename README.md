# CS 100 RSHELL
Winter Quarter 2019
Melanie Aguilar, SID: 862033156
Surya Singh, SID: 862033627

##Introduction
Create a shell that can (1) print a command prompt, (2) read in a line of commands from standard input, and (3) Execute commands using fork, execvp and waitpid. The command prompt should be able to print a line containing “$” in order to execute and run commands inputted by the user. The prompt should be able to read the line of commands and determine which command the user is referring to and execute in a specific manner.  Execvp command will be used to run the executable from one of the PATH environment variable  locations. In this assignment,we used a composite pattern, which helps in partitioning a group of objects. The inputs are taken in from the user, then through the fork(), execvp(), wait(), we are going to run and execute the commands based on connectors. 

##Diagram
![GitHub Logo](/images/uml.png)
Format: ![Alt Text]assignment-cs-100-melanie-surya/images/uml.png
      

