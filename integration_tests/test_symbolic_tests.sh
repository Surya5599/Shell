#!/bin/sh
# tests primarily for the symbolic tests commands execution

cd ..

./rshell << EOF
[ -e shell.cpp ] && echo "shell is a file/dir"
[ -d pareCommands.h ] || echo "pareCommands is not a directory"
[ -d ../assignment3 ] && echo "is a dir"
[ -f Command.h ] && echo "is a file" 
[ -d shell.cpp ] || echo is not a directory 
[ -f multipleCommand.cpp ] && [ -f multipleCommand.h ] && echo "is a file"
[ -d multipleCommand.cpp ] || [ -d multipleCommand.h ] || [ -d ../assignment3 ] && echo "is a directoy"
[ -e shell.cpp ] && echo "shell is a file/dir" && [ -d shell.cpp ] && echo "shell is a dir" || [ -f shell.cpp ] && echo "shell is a file"
[ -e ../assignment3 ] && echo "is a file/dir" && [ -d ../assignment3 ] && echo "assignment3 is a dir" || [ -f ../assignment3 ] && echo "is a file"
[ -e mel.cpp ] && echo "is a file/dir" || echo "is not a file/dir"
[ -e Command.h ] && [ -e multipleCommand.h ] && [ -e multipleCommand.cpp ] && [ -e singleCommand.h ] && [ -e singleCommand.cpp ] && [ -e ../assignment2 ] && echo "are files/directories" && [ -f Command.h ] && [ -f multipleCommand.h ] && [ -f multipleCommand.cpp ] && [ -f singleCommand.h ] && [ -f singleCommand.cpp ] && echo "are files"
[ -e Command.h ] && [ -e multipleCommand.h ] && [ -e multipleCommand.cpp ] && [ -e singleCommand.h ] && [ -e singleCommand.cpp ] && [ -e ../assignment2 ] && echo "are files/directories" && [ -d ../assignment2 ] && echo "is directory"
[ -e singleCommand.h ] && echo "is file/directory" || echo "is not file/directory"
exit
EOF
