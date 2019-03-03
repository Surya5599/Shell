#!/bin/sh
# tests primarily for the test commands execution
cd ..

./a.out << EOF
test -e shell.cpp && echo "shell is a file/dir"
test -d pareCommands.h || echo "pareCommands is not a directory"
test -d ../assignment3 && echo "is a dir"
test -f Command.h && echo "is a file"
test -d shell.cpp || echo is not a dir
test -f multipleCommand.cpp && test -f multipleCommand.h && echo "is a file"
test -d multipleCommand.cpp || test -d multipleCommand.h || test -d ../assignment3 && echo "is a directoy"
test -e shell.cpp && echo "shell is a file/dir" && test -d shell.cpp && echo "shell is a dir" || test -f shell.cpp && echo "shell is a file"
test -e ../assignment3 && echo "is a file/dir" && test -d ../assignment3 && echo "assignment3 is a dir" || test -f ../assignment3 && echo "is a file"
test -e mel.cpp && echo "is a file/dir" || echo "is not a file/dir"
test -e Command.h && test -e multipleCommand.h && test -e multipleCommand.cpp && test -e singleCommand.h && test -e singleCommand.cpp && test -e ../assignment2 && echo "are files/directories" && test -f Command.h && test -f multipleCommand.h && test -f multipleCommand.cpp && test -f singleCommand.h && test -f singleCommand.cpp && echo "are files"
test -e Command.h && test -e multipleCommand.h && test -e multipleCommand.cpp && test -e singleCommand.h && test -e singleCommand.cpp && test -e ../assignment2 && echo "are files/directories" && test -d ../assignment2 && echo "is directory"
test -e singleCommand.h && echo "is file/directory" || echo "is not file/directory"
exit
EOF
