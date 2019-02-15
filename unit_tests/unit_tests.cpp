#include "gtest/gtest.h"
#include "Command.h"
#include "singleCommand.h"
#include "multipleCommand.h"

TEST(SingleCommandTest, ECHO){   
    singleCommand* s1 = new singleCommand("echo love cs");
    s1->Parse();
    EXPECT_EQ(true, s1->runCommand());
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
