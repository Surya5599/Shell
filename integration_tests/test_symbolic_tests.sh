#!/bin/sh
# tests primarily for the symbolic tests commands execution

cd ..

./rshell << EOF
[ -e src/shell.cpp ] && echo "shell.cpp is a file/dir"
[ -d src/pareCommands.h ] || echo "pareCommands.h is not a directory"
[ -d src ] && echo "src is a dir"
[ -f src/Command.h ] && echo "Command.h is a file" 
[ -d shell.cpp ] || echo shell.cpp is not a directory 
[ -f src/multipleCommand.cpp ] && [ -f src/multipleCommand.h ] && echo "multipleCommand.cpp and multipleCommand.h are files"
[ -d src/multipleCommand.cpp ] || [ -d src/multipleCommand.h ] || [ -d integration_tests ] && echo "integration_tests is a directoy"
[ -e src/shell.cpp ] && echo "shell.cpp is a file/dir" && [ -d src/shell.cpp ] && echo "shell.cpp is a dir" || [ -f src/shell.cpp ] && echo "shell.cpp is a file"
[ -e integration_tests ] && echo "integration_tests is a file/dir" && [ -d integration_tests ] && echo "integration_tests is a dir" || [ -f integration_tests ] && echo "integration_tests is a file"
[ -e mel.cpp ] && echo "mel.cpp is a file/dir" || echo "mel.cpp is not a file/dir"
[ -e src/Command.h ] && [ -e src/multipleCommand.h ] && [ -e src/multipleCommand.cpp ] && [ -e src/singleCommand.h ] && [ -e src/singleCommand.cpp ] && [ -e unit_tests ] && echo "are files/directories" && [ -f src/Command.h ] && [ -f src/multipleCommand.h ] && [ -f src/multipleCommand.cpp ] && [ -f src/singleCommand.h ] && [ -f src/singleCommand.cpp ] && echo "are files"
[ -e src/Command.h ] && [ -e src/multipleCommand.h ] && [ -e src/multipleCommand.cpp ] && [ -e src/singleCommand.h ] && [ -e src/singleCommand.cpp ] && [ -e unit_tests ] && echo "are files/directories" && [ -d unit_tests ] && echo "unit_tests is directory"
[ -e src/singleCommand.h ] && echo "singleCommand.h is file/directory" || echo "singleCommand.h is not file/directory"
exit
EOF
