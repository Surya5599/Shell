#!/bin/sh

cd ..

./rshell << EOF
echo hello && echo hi
echo 1 || echo 2
echo 1 ; echo 2
echo 1 && echo 2 || echo 3 ; echo 4
ls ; mkdir newDir ; ls ; rm -rf newDir ; ls
echo "hello && goodbye" || echo hello
echo "hello && goodbye" && echo "hello || goodbye"
ls -a; echo hello && mkdir newDir || echo world; git status; rm -rf newDir
echo 1 && echo 2 && echo 3 ; echo 4 ; echo 5; echo 6
exit
EOF

