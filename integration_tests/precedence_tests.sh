#!/bin/sh
# tests primarily for the precedence being respected

cd ..


./rshell << EOF
echo 1  && echo "world" ; (echo hi && echo "world")
echo hi && echo "world" || (echo hi && echo "world")
echo hi && echo "world" && (echo hi && echo "world")
echo hi && ls # (echo hi && echo "world")
(echo 1 && echo 2) && (echo 3 && echo 4) && (echo 5 && echo 6)
(echo 1 || echo 2) && echo 3
(echo 1 || echo 2) && echo 3
(echo 1 || (echo 2 && echo 3))
(echo 1 || (echo 2 && echo 3) && (echo 4 && echo 5))
(echo 1 && (echo 2 && echo 3) || (echo 4 ; echo 5))
(echo 1 ; (echo 2 && echo 3)) && echo 4
(dog && (echo 3 && echo 5))
(echo hello && echo hi
echo "(hello there)" && (echo 2 && echo 4)
(exit && echo 1) && echo 2;
(exit && echo 1) || echo 2;
(exit && echo 1) ; echo 2;
echo 1 && (exit && echo 2 && echo 3) && echo 4
echo 1 ; (echo 2 ; exit || echo 3) && echo 5
echo 1 ; (echo 3 && echo 4 ; exit) || echo 6
exit
EOF
