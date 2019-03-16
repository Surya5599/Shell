#!/bin/sh
# tests primarily for the output redirection

cd ..

./rshell << EOF
echo hello | tr a-z A-Z
echo HeLLO | tr a-z A-Z
echo ThIs is A TeST | tr a-z A-Z | tr A-Z a-z
cat < inputfile | tr a-z A-Z
cat < inputfile 2 | tr a-z A-Z
cat < inputfile | tr a-z A-Z | sort                                                                                                     
cat < inputfile | tr a-z A-Z | sort > outputfile
cat < inputfile2 | tr A-Z a-z | tee outputfile | tr a-z A-Z >> outputfile
exit
EOF
