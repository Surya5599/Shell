#!/bin/sh
# tests primarily for the input redirection

cd ..

./rshell << EOF
cat < inputfile
cat < inputfile && echo A
cat < inputfile > outputfile
cat < inputfile >> outputfile
cat < nofile || echo file doesn't exist
cat < inputfile && cat < inputfile2
exit
EOF
