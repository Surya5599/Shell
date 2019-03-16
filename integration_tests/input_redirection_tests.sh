#!/bin/sh
# tests primarily for the input redirection

cd ..

./rshell << EOF
cat < integration_tests/inputfile
cat < integration_tests/inputfile && echo A
cat < integration_tests/inputfile > integration_tests/outputfile
echo "OUTPUTFILE " && cat < integration_tests/outputfile
cat < integration_tests/inputfile >> integration_tests/outputfile
echo "OUTPUTFILE " && cat < integration_tests/outputfile
cat < integration_tests/nofile || echo file doesn't exist
cat < integration_tests/inputfile && cat < integration_tests/inputfile2
rm integration_tests/outputfile
exit
EOF
