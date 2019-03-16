#!/bin/sh
# tests primarily for the output redirection

cd ..

./rshell << EOF
echo A > outputfile
echo B >> outputfile
echo D > outputfile2 && echo E >> outputfile2
echo F >> outputfile2 || echo G > outputfile2
echo H > outputfile3 ; echo I > outputfile4
echo A B C D E F > outputfile5
exit
EOF
