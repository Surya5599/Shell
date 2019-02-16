#!/bin/sh

cd ..

./rshell << EOF
echo hello #hi
echo con # hi && echo this wont print
echo "hello # hi"
ls #-a
echo hello #&& echo hi
#exit
echo hi #; echo hi
#echo hello
exit
EOF
