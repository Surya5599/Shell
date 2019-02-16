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

TEST(SingleCommandTest, LS){
    
    singleCommand* s2 = new singleCommand("ls");
    s2->Parse();
    s2->runCommand();


}


TEST(SingleCommandTest, MKDIR){
    
    singleCommand* s3 = new singleCommand("mkdir new");
    s3->Parse();
    s3->runCommand();

}


TEST(SingleCommandTest, WrongCommand){
    
    singleCommand* s3 = new singleCommand("wrong");
    s3->Parse();
    s3->runCommand();

}


TEST(MultipleCommandTest, Mixed1) {
    
    multipleCommand* m1 = new multipleCommand("echo hello || ls ; echo "my && name" && echo "is || mel" && ls");
    m1->Parse();
    m1->runCommand();
    EXPECT_EQ();
    
}

TEST(MultipleCommandTest, Mixed2) {
    
    multipleCommand* m2 = new multipleCommand("ls -a; echo hello; mkdir test");
    m2->Parse();
    m2->runCommand();
    EXPECT_EQ();
        
}

TEST(MultipleCommandTest, Mixed3) {
    
    multipleCommand* m3 = new multipleCommand("ls -a; echo hello && mkdir test || echo world; git status");
    m3->Parse();
    m3->runCommand();
    EXPECT_EQ();
}


TEST(MultipleCommandTest, Mixed4){
    
    multipleCommand* m4 = new multipleCommand(echo "hello" ; ls || echo "don't print");
    m4->Parse();
    m5->runCommand();
    EXPECT_EQ();

}

TEST(CommentedCommandTest, Comment1){
    singleCommand* s1 = new singleCommand("echo love cs # wont print");
    s1->Parse();
    s1->runCommand();
    
}


TEST(CommentedCommandTest, Comment2){
    singleCommand* s1 = new singleCommand("ls -a #ls");
    s1->Parse();
    s1->runCommand();

}

TEST(CommentedCommandTest, Comment3){
    multipleCommand* m1 = new multipleCommand("echo hello #wont print ; echo hi # dont print");
    m1->Parse();
    m1->runCommand();

}

TEST(CommentedCommandTest, Comment4){
    multipleCommand* m1 = new multipleCommand("echo hello  ; echo hi # dont print ; echo this shouldnt print");
    m1->Parse();
    m1->runCommand();


}


TEST(CommentedCommandTest, Comment5){
    multipleCommand* m1 = new multipleCommand( "#echo hello  ; echo hi dont print");
    m1->Parse();
    m1->runCommand();


}


TEST(ExitCommandTest, Exit1){
    singleCommand* s1 = new singleCommand("exit");
    s1->Parse();
    s1->runCommand();
    EXPECT_EQ();
    
}
TEST(ExitCommandTest, Exit2){
    multipleCommand* m1 = new multipleCommand( "echo hello  ; exit");
    m1->Parse();
    m1->runCommand();
    EXPECT_EQ();
}
TEST(ExitCommandTest, Exit3){
    multipleCommand* m1 = new multipleCommand( "echo hello || exit");
    m1->Parse();
    m1->runCommand();
    EXPECT_EQ();
}
TEST(ExitCommandTest, Exit4){
    multipleCommand* m1 = new multipleCommand( "echo hello && exit");
    m1->Parse();
    m1->runCommand();
    EXPECT_EQ();
}
TEST(ExitCommandTest, Exit5){
    multipleCommand* m1 = new multipleCommand( "wrong command || exit");
    m1->Parse();
    m1->runCommand();
    EXPECT_EQ();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}














