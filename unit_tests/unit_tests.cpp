#include "gtest/gtest.h"
#include "Command.h"
#include "singleCommand.h"
#include "multipleCommand.h"
#include "pareCommands.h"
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
    
    singleCommand* s2 = new singleCommand("echo A");
    s2->Parse();
    testing::internal::CaptureStdout();
    s2->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "A";
    EXPECT_EQ(expectedOutput, output);

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
    
    multipleCommand* m1 = new multipleCommand("echo hello || ls ; echo \"my && name\" && echo \"is || mel\" && echo 3");
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "hello\nmy && name\nis || mel\n3\n";
    EXPECT_EQ(expectedOutput, output);
}

TEST(MultipleCommandTest, Mixed2) {
    
    multipleCommand* m2 = new multipleCommand("echo A; echo hello; echo B; echo C");
    m2->Parse();
     testing::internal::CaptureStdout();
    m2->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "A\nhello\nB\nC\n";
    EXPECT_EQ(expectedOutput, output);   
}

TEST(MultipleCommandTest, Mixed3) {
    
    multipleCommand* m3 = new multipleCommand("echo hello || echo B ; echo hi || echo world || echo C");
    m3->Parse();
    testing::internal::CaptureStdout();
    m3->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "hello\nhi\n";
    EXPECT_EQ(expectedOutput, output);
}


TEST(MultipleCommandTest, Mixed4){
    
    multipleCommand* m4 = new multipleCommand("echo \"hello ; ls\" || echo \"don't print\"");
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
    singleCommand* s1 = new singleCommand("echo A # B");
    s1->Parse();
    testing::internal::CaptureStdout();
    s1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    string expectedOutput = "A\n";
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

TEST(PrecedenceTest, Precedence1){
    string input = "(echo 1 && echo 2) && echo 3";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n2\n3\n", output);
}

TEST(PrecedenceTest, Precedence2){
    string input = "(echo 1 && echo 2) || echo 3";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n2\n", output);
}

TEST(PrecedenceTest, Precedence3){
    string input = "(echo 1 || echo 2) || echo 3";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n", output);
}

TEST(PrecedenceTest, Precedence4){
    string input = "(echo 1 || echo 2) && echo 3";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n3\n", output);
}

TEST(PrecedenceTest, Precedence5){
    string input = "(echo 1 || echo 2) ; echo 3";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n3\n", output);
}

TEST(PrecedenceTest, Precedence6){
    string input = "(echo 1 ; echo 2) ; echo 3";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n2\n3\n", output);
}

TEST(PrecedenceTest, Precedence7){
    string input = "(echo 1 ; echo 2) ; (echo 3 && echo 4)";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n2\n3\n4\n", output);
}

TEST(PrecedenceTest, Precedence8){
    string input = "(echo 1 ; echo 2) || (echo 3 && echo 4)";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n2\n", output);
}

TEST(PrecedenceTest, Precedence9){
    string input = "(echo 1 ; echo 2) || (echo 3)";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n2\n", output);
}


TEST(PrecedenceTest, Precedence10){
    string input = "(echo 1 ; (echo 3 && echo 4))";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n3\n4\n", output);
}

TEST(PrecedenceTest, Precedence11){
    string input = "(echo 1 || (echo 3 && echo 4))";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n", output);
}

TEST(PrecedenceTest, Precedence12){
    string input = "(echo 1 || (echo 3 && echo 4) && (echo 5 && echo 6))";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("1\n5\n6\n", output);
}

TEST(PrecedenceTest, Precedence13){
    string input = "(dog || (echo 3 && echo 4) && (echo 5 && echo 6))";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("3\n4\n5\n6\n", output);
}

TEST(PrecedenceTest, Precedence14){
    string input = "(exit && echo 4) && (echo 5 && echo 6)";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("5\n6\n", output);
}

TEST(PrecedenceTest, Precedence15){
    string input = "(exit && echo 4) || (echo 5 && echo 6)";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(PrecedenceTest, Precedence16){
    string input = "(exit && (echo 5 && echo 6))";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(PrecedenceTest, Precedence17){
    string input = "(exit && (echo 5 && echo 6)";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Syntax Error: Parenthesis Missing\n", output);
}

TEST(PrecedenceTest, Precedence18){
    string input = "(exit && #(echo 5 && echo 6)";
    pareCommands* p1 = new pareCommands(input);
    p1->Parse();
    testing::internal::CaptureStdout();
    p1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("Syntax Error: Parenthesis Missing\n", output);
}


TEST(TestCommandTest, Test1){
    string input = "test -e src";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(TestCommandTest, Test2){
    string input = "test -f src";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}
TEST(TestCommandTest, Test3){
    string input = "test -d src";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(TestCommandTest, Test4){
    string input = "test src";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(TestCommandTest, Test5){
    string input = "test -e src/shell.cpp";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}
TEST(TestCommandTest, Test6){
    string input = "test -d src/shell.cpp";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}
TEST(TestCommandTest, Test7){
    string input = "test -f src/shell.cpp";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(TestCommandTest, Test8){
    string input = "test src/shell.cpp";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(TestCommandTest, Test9){
string input = "test src/shellll.cpp";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}


TEST(TestCommandTest, Test10){
string input = "test -e src/shellll.cpp";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}

TEST(TestCommandTest, Test11){
string input = "test -f src/shellll.cpp";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}

TEST(TestCommandTest, Test12){
string input = "test -d src/shellll.cpp";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}

TEST(SymbolicTestCommandTest, STest1){
    string input = "[ -e src ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(SymbolicTestCommandTest, STest2){
    string input = "[ -f src ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}
TEST(SymbolicTestCommandTest, STest3){
    string input = "[ -d src ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(SymbolicTestCommandTest, STest4){
    string input = "[ src ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(SymbolicTestCommandTest, STest5){
    string input = "[ -e src/shell.cpp ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}
TEST(SymbolicTestCommandTest, STest6){
    string input = "[ -d src/shell.cpp ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}

TEST(SymbolicTestCommandTest, STest7){
    string input = "[ -f src/shell.cpp ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(SymbolicTestCommandTest, STest8){
    string input = "[ src/shell.cpp ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(TRUE)\n", output);
}

TEST(SymbolicTestCommandTest, STest9){
string input = "[ src/shellll.cpp ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}


TEST(SymbolicTestCommandTest, STest10){
string input = "[ -e src/shellll.cpp ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}

TEST(SymbolicTestCommandTest, STest11){
string input = "[ -f src/shellll.cpp ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}

TEST(SymbolicTestCommandTest, Test12){
string input = "[ -d src/shellll.cpp ]";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("(FALSE)\n", output);
}

TEST(SymbolicTestCommandTest, Test12){
    string input = "cat < integration_tests/inputfile";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(InputRed, Test1){
    string input = "cat < integration_tests/inputfile";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(InputRed, Test2){
    string input = "cat < integration_tests/inputfile > integration_tests/outputfile";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(InputRed, Test3){
    string input = "cat < integration_tests/inputfile2 >> integration_tests/outputfile";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(InputRed, Test4){
    string input = "cat < integration_tests/inputfile && echo A";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(InputRed, Test5){
    string input = "cat < integration_tests/inputfile || echo A";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(InputRed, Test6){
    string input = "cat < integration_tests/inputfile ; echo A";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}
TEST(InputRed, Test7){
    string input = "cat < integration_tests/inputfile && cat < integration_tests/inputfile2";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(InputRed, Test8){
    string input = "cat < integration_tests/inputfile || cat < integration_tests/inputfile2";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(OutputRed, Test1){
    singleCommand* s1 = new singleCommand("rm outputfile");
    s1->Parse();
    s1->runCommand();
    string input = "echo A > outputfile";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(OutputRed, Test2){
    string input = "echo B >> outputfile";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}


TEST(OutputRed, Test4){
    string input = "echo C > outputfile && echo D >> outputfile";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(OutputRed, Test5){
    string input = "echo F > outputfile || echo A";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}

TEST(OutputRed, Test6){
    string input = "echo A > outputfile ; echo B > outputfile";
    multipleCommand* m1 = new multipleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("", output);
}
TEST(Pipe, Test1){
    string input = "echo A B c D e F g | tr a-z A-Z";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("A B C D E F G\n", output);
}
TEST(Pipe, Test2){
    string input = "echo A B c D e F g | tr A-Z a-z";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a b c d e f g\n", output);
}

TEST(Pipe, Test3){
    string input = "cat < inputfile | tr A-Z a-z";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a b c d e f g\n", output);
}

TEST(Pipe, Test4){
    string input = "cat < inputfile | tr A-Z a-z | sort";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a b c d e f g\n", output);
}

TEST(Pipe, Test5){
    string input = "cat < inputfile | tr A-Z a-z | sort > output";
    singleCommand* m1 = new singleCommand(input);
    m1->Parse();
    testing::internal::CaptureStdout();
    m1->runCommand();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ("a b c d e f g\n", output);
}


//extensive Exit testing will be done in integration because the exit here exits the google test stopping multiple exit functions
//
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}













