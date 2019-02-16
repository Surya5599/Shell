#!/bin/sh

cd ..


./rshell << EOF
echo hello
dog
ls
mkdir newDir
ls
rm -rf newDir
ls
echo "hello && godybe"
echo "hello ; goodbye"
echo "hello || goodbye"
echo exiting
exit
EOF



