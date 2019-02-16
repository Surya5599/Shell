#!/bin/sh

cd ..

./rshell << EOF
echo Running "echo hello && echo hi"
echo hello && echo hi
echo Running "echo hello || ls"
echo hello || ls
exit
EOF

