CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest src)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(
    shell.cpp
    singleCommand.cpp
    multipleCommand.cpp
)

ADD_EXECUTABLE(test
   unit_test.cpp
   
)

TARGET_LINK_LIBRARIES(rshell shell.cpp)
TARGET_LINK_LIBRARIES(test gtest)

TARGET_COMPILE_DEFINITIONS(rshell PRIVATE gtest_disable_pthreads=ON)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON) 

