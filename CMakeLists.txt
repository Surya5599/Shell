CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


include_directories(
        ${PROJECT_SOURCE_DIR}/unit_tests
        ${PROJECT_SOURCE_DIR}/src
)


ADD_SUBDIRECTORY(googletest)
SET(CMAKE_CXX_STANDARD 11)


ADD_EXECUTABLE(rshell
    ${PROJECT_SOURCE_DIR}/src/shell.cpp
     ${PROJECT_SOURCE_DIR}/src/singleCommand.cpp
     ${PROJECT_SOURCE_DIR}/src/multipleCommand.cpp
     ${PROJECT_SOURCE_DIR}/src/pareCommands.cpp
     ${PROJECT_SOURCE_DIR}/src/Symbols.cpp
)



ADD_EXECUTABLE(test
   ${PROJECT_SOURCE_DIR}/unit_tests/unit_tests.cpp
   ${PROJECT_SOURCE_DIR}/src/singleCommand.cpp
     ${PROJECT_SOURCE_DIR}/src/multipleCommand.cpp
	${PROJECT_SOURCE_DIR}/src/pareCommands.cpp
	${PROJECT_SOURCE_DIR}/src/Symbols.cpp

)
TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
