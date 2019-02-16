#!/bin/sh

cd ..

./rshell << EOF
exit
EOF
echo "exited"
./rshell << EOF
echo hello || exit
exit
EOF
./rshell << EOF
echo hello && exit
EOF
echo "exited"
./rshell << EOF
echo hello ; exit
EOF
echo "exited"

