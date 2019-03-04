#!/bin/sh
# tests primarily for the test commands execution
cd ..

./rshell << EOF
test -e src/shell.cpp && echo "shell.cpp is a file/dir"
test -d src/pareCommands.h && echo "pareCommands.h is a directory" || echo "pareCommands.h is not a directory"
test -d src && echo "is a dir"
test -f src/Command.h && echo "is a file"
test -d src/shell.cpp || echo "shell.cpp is not a dir"
test -f src/multipleCommand.cpp && test -f src/multipleCommand.h && echo "multipleCommand.cpp and multipleCommand.h are files"
test -d src/multipleCommand.cpp || test -d src/multipleCommand.h || test -d integration_tests && echo "integration_tests is a directoy"
test -e src/shell.cpp && echo "shell.cpp is a file/dir" && test -d src/shell.cpp && echo "shell/cpp is a dir" || test -f src/shell.cpp && echo "shell.cpp is a file"
test -e unit_tests && echo "is a file/dir" && test -d src && echo "src is a dir" || test -f integration_tests && echo "is a file"
test -e src/mel.cpp && echo "mel.cpp is a file/dir" || echo "mel.cpp is not a file/dir"
test -e src/Command.h && test -e src/multipleCommand.h && test -e src/multipleCommand.cpp && test -e src/singleCommand.h && test -e src/singleCommand.cpp && test -e src && echo "are files/directories" && test -f src/Command.h && test -f src/multipleCommand.h && test -f src/multipleCommand.cpp && test -f src/singleCommand.h && test -f src/singleCommand.cpp && echo "are files"
test -e src/Command.h && test -e src/multipleCommand.h && test -e src/multipleCommand.cpp && test -e src/singleCommand.h && test -e src/singleCommand.cpp && test -e unit_tests && echo "are files/directories" && test -d unit_tests && echo "unit_tests is directory"
test -e src/singleCommand.h && echo "singleCommand.h is file/directory" || echo "singleCommand.h is not file/directory"
exit
EOF
