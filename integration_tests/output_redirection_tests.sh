#!/bin/sh
# tests primarily for the output redirection

cd ..

./rshell << EOF
echo A > integration_tests/outputfile
echo "outputfile: " && cat < integration_tests/outputfile
echo B >> integration_tests/outputfile
echo "outputfile: " && cat < integration_tests/outputfile
echo D > integration_tests/outputfile2 && echo E >> integration_tests/outputfile2
echo "outputfile2: " && cat < integration_tests/outputfile2
echo F >> integration_tests/outputfile2 || echo G > integration_tests/outputfile2
echo "outputfile2: " && cat < integration_tests/outputfile2
echo H > integration_tests/outputfile3 ; echo I > integration_tests/outputfile4
echo "outputfile3: " && cat < integration_tests/outputfile3
echo "outputfile4: " && cat < integration_tests/outputfile4
echo A B C D E F > integration_tests/outputfile
echo "outputfile: " && cat < integration_tests/outputfile
rm integration_tests/outputfile
rm integration_tests/outputfile2
rm integration_tests/outputfile3
rm integration_tests/outputfile4
exit
EOF
