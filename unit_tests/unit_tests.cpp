#include "gtest/gtest.h"
#include "Command.h"
#include "singleCommand.h"
#include "multipleCommand.h"
#include <sstream>

using namespace std;

TEST(SingleCommandTest, ECHO){   
    singleCommand* s1 = new singleCommand("echo love cs");
    s1->Parse();
    testing::internal::CaptureStdout();
    s1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("love cs\n", output);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
