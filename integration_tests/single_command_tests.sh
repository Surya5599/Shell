#!/bin/sh

cd ..


./rshell << EOF
echo Showing Current Directories running "ls":
ls
echo Making new directory called newDir running "mkdir newDir":
mkdir newDir
echo Showing new list of directories running "ls":
ls
echo Removing newDir running "rm -rf newDir":
rm -rf newDir
echo Showing list of directories running "ls":
ls
echo exiting using "exit":
exit
EOF



