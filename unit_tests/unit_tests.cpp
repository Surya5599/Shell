#include "gtest/gtest.h"
#include "Command.h"
#include "singleCommand.h"
#include "multipleCommand.h"

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
    testing::internal::CaptureStdout();
    s2->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "bin\nCMakeCache.txt\nCMakeFiles\ncmake_install.cmake\nCMakeLists.txt\ngoogletest\nimages\nintegration_tests\nlib\nMakefile\nnames.txt\nREADME.md\nrshell\nsrc\ntest\nunit_tests\n";
    EXPECT_EQ(expectedOutput, output);

}


TEST(SingleCommandTest, MKDIRandRM){
    
    singleCommand* s3 = new singleCommand("mkdir new");
    s3->Parse();
    s3->runCommand();
    singleCommand* s2 = new singleCommand("ls");
    s2->Parse();
    testing::internal::CaptureStdout();
    s2->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "bin\nCMakeCache.txt\nCMakeFiles\ncmake_install.cmake\nCMakeLists.txt\ngoogletest\nimages\nintegration_tests\nlib\nMakefile\nnames.txt\nnew\nREADME.md\nrshell\nsrc\ntest\nunit_tests\n";
    EXPECT_EQ(expectedOutput, output);
    singleCommand* s4 = new singleCommand("rm -rf new");
    s4->Parse();
    s4->runCommand();
    testing::internal::CaptureStdout();
    s2->runCommand();
    string output2 = testing::internal::GetCapturedStdout();
    string expectedOutput2 = "bin\nCMakeCache.txt\nCMakeFiles\ncmake_install.cmake\nCMakeLists.txt\ngoogletest\nimages\nintegration_tests\nlib\nMakefile\nnames.txt\nREADME.md\nrshell\nsrc\ntest\nunit_tests\n";
    EXPECT_EQ(expectedOutput2, output2);

}


TEST(SingleCommandTest, WrongCommand){
    
    singleCommand* s3 = new singleCommand("wrong");
    s3->Parse();
    testing::internal::CaptureStdout();
    s3->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}


TEST(MultipleCommandTest, Mixed1) {
    
    multipleCommand* m1 = new multipleCommand("echo hello || ls ; echo \"my && name\" && echo \"is || mel\" && ls");
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "hello\nmy && name\nis || mel\nbin\nCMakeCache.txt\nCMakeFiles\ncmake_install.cmake\nCMakeLists.txt\ngoogletest\nimages\nintegration_tests\nlib\nMakefile\nnames.txt\nREADME.md\nrshell\nsrc\ntest\nunit_tests\n";
    EXPECT_EQ(expectedOutput, output);
}

TEST(MultipleCommandTest, Mixed2) {
    
    multipleCommand* m2 = new multipleCommand("ls -a; echo hello; mkdir newDir; ls");
    m2->Parse();
     testing::internal::CaptureStdout();
    m2->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = ".\n..\nbin\nCMakeCache.txt\nCMakeFiles\ncmake_install.cmake\nCMakeLists.txt\n.git\n.gitignore\n.gitmodules\ngoogletest\nimages\nintegration_tests\nlib\nMakefile\nnames.txt\nREADME.md\nrshell\nsrc\ntest\nunit_tests\nhello\nbin\nCMakeCache.txt\nCMakeFiles\ncmake_install.cmake\nCMakeLists.txt\ngoogletest\nimages\nintegration_tests\nlib\nMakefile\nnames.txt\nnewDir\nREADME.md\nrshell\nsrc\ntest\nunit_tests\n";
    EXPECT_EQ(expectedOutput, output);
    multipleCommand* m6 = new multipleCommand("rm -rf newDir");
    m6->Parse();
    m6->runCommand();    
}

TEST(MultipleCommandTest, Mixed3) {
    
    multipleCommand* m3 = new multipleCommand("echo hello || ls -1 ; echo hi || echo world || git status");
    m3->Parse();
    testing::internal::CaptureStdout();
    m3->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "hello\nhi\n";
    EXPECT_EQ(expectedOutput, output);
}


TEST(MultipleCommandTest, Mixed4){
    
    multipleCommand* m4 = new multipleCommand("echo \"hello\" ; ls || echo \"don't print\"");
    m4->Parse();
    testing::internal::CaptureStdout();
    m4->runCommand();
    string output = testing::internal::GetCapturedStdout();
     string expectedOutput = "hello ; ls\n";
    EXPECT_EQ(expectedOutput, output);

}

TEST(CommentedCommandTest, Comment1){
    singleCommand* s1 = new singleCommand("echo love cs # wont print");
    s1->Parse();
    testing::internal::CaptureStdout();
    s1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "love cs\n");
}


TEST(CommentedCommandTest, Comment2){
    singleCommand* s1 = new singleCommand("ls # -a");
    s1->Parse();
    testing::internal::CaptureStdout();
    s1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "bin\nCMakeCache.txt\nCMakeFiles\ncmake_install.cmake\nCMakeLists.txt\ngoogletest\nimages\nintegration_tests\nlib\nMakefile\nnames.txt\nREADME.md\nrshell\nsrc\ntest\nunit_tests\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST(CommentedCommandTest, Comment3){
    multipleCommand* m1 = new multipleCommand("echo hello #wont print ; echo hi # dont print");
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("hello\n", output);
}

TEST(CommentedCommandTest, Comment4){
    multipleCommand* m1 = new multipleCommand("echo hello ; echo hi # dont print ; echo this shouldnt print");
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("hello\nhi\n", output);

}


TEST(CommentedCommandTest, Comment5){
    multipleCommand* m1 = new multipleCommand( "#echo hello  ; echo hi dont print");
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(ExitCommandTest, Exit3){
    multipleCommand* m1 = new multipleCommand( "echo hello || exit");
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("hello\n", output);
}

//extensive Exit testing will be done in integration because the exit here exits the google test stopping multiple exit functions
//
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}













