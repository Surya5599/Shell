#!/bin/sh

cd ..

./rshell << EOF
echo hello && echo hi
echo hello || ls
echo Greeting "hello"
echo Showing Current Status "status"
status
echo Showing files in Current directory
ls
echo Create New file in directory "
echo
echo Remove file from direcory "rm
echo
echo Show existing files in Current Directory "ls"
echo ls 
echo Leaving "goodbye"
goodbye
exit
EOF

