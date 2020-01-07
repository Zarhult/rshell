#ifndef __GTESTS_HPP__
#define __GTESTS_HPP__

#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "../src/base.hpp"
#include "../src/connectorand.hpp"
#include "../src/connectoror.hpp"
#include "../src/connectorsemicolon.hpp"
#include "../src/exe.hpp"
#include "../src/parser.hpp"
#include "../src/nightmare.hpp"

using namespace std;

TEST(ExeTest, ExeFail)
{
    vector<string> cmd = {"meme"}; //nonexistent cmommand
    Base* exe = new Exe(cmd);
    EXPECT_EQ(exe->execute(), -1);
}

TEST(ExeTest, ExePass)
{
    vector<string> cmd = {"ls"};
    Base* exe = new Exe(cmd);
    EXPECT_EQ(exe->execute(), 0);
}

TEST(ConnectTestAnd, Fail) {
    vector<string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    vector<string> cmd2;
    cmd2.push_back("ls");

    Base* exe = new Exe(cmd);
    Base* exe2 = new Exe(cmd2);

    Base* connect = new ConnectorAnd(exe, exe2);

    EXPECT_EQ(connect->execute(), -1);
}

TEST(ConnectTestAnd, Pass) {
    vector<string> cmd;
    cmd.push_back("echo");
    cmd.push_back("hello");

    vector<string> cmd2;
    cmd2.push_back("ls");

    Base* exe = new Exe(cmd);
    Base* exe2 = new Exe(cmd2);

    Base* connect = new ConnectorAnd(exe, exe2);

    EXPECT_EQ(connect->execute(), 0);
}

TEST(ConnectTestOr, Fail) {
    vector<string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    Base* exe = new Exe(cmd);

    Base* connect = new ConnectorOr(exe, exe);

    EXPECT_EQ(connect->execute(), -1);
}

TEST(ConnectTestOr, Pass) {
    vector<string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    vector<string> cmd2;
    cmd2.push_back("ls");

    Base* exe = new Exe(cmd);
    Base* exe2 = new Exe(cmd2);

    Base* connect = new ConnectorOr(exe, exe2);

    EXPECT_EQ(connect->execute(), 0);
}

TEST(ConnectTestSemicolon, Fail) {
    vector<string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    Base* exe = new Exe(cmd);

    Base* connect = new ConnectorSemicolon(exe, exe);

    EXPECT_EQ(connect->execute(), -1);
}

TEST(ConnectTestSemicolon, Pass) {
    vector<string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    vector<string> cmd2;
    cmd2.push_back("echo");
    cmd2.push_back("plzwork");

    Base* exe = new Exe(cmd);
    Base* exe2 = new Exe(cmd2);

    Base* connect = new ConnectorSemicolon(exe, exe);
    Base* connect2 = new ConnectorSemicolon(connect, exe2);

    EXPECT_EQ(connect2->execute(), 0);
}

TEST(ParenthesesTest, LeftSide) {
    string input = "(echo a && echo b) && echo c";
    vector<string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    cout << "Expect: a b c" << endl;
    EXPECT_EQ(exe->execute(), 0);

}

TEST(ParenthesesTest, RightSide) {
    string input = "echo a && (echo b && echo c)";
    vector<string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    cout << "Expect: a b c" << endl;
    EXPECT_EQ(exe->execute(), 0);
}

TEST(ParenthesesTest, BothSides) {
    string input = "(echo a && echo b) && (echo c && echo d)";
    vector<string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    cout << "Expect: a b c d" << endl;
    EXPECT_EQ(exe->execute(), 0);
}

TEST(ParenthesesTest, Whole) {
    string input = "(echo a && echo b && echo c && echo d)";
    vector<string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    cout << "Expect: a b c d" << endl;
    EXPECT_EQ(exe->execute(), 0);
}

TEST(TestFlagE, ExistingFile) {
    string input = "test -e src";
    vector<string> cmd = parse(input);
    Base* test = new Exe(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestFlagE, NonExistingFile) {
   string input = "test -e meme";
   vector<string> cmd = parse(input);
   Base* test = new Exe(cmd);

   EXPECT_NE(test->execute(), 0);
}

TEST(TestFlagD, IsDirectory) {
   string input = "test -d src";
   vector<string> cmd = parse(input);
   Base* test = new Exe(cmd);

   EXPECT_EQ(test->execute(), 0);
}

TEST(TestFlagD, NotDirectory) {
   string input = "test -d CMakeLists.txt";
   vector<string> cmd = parse(input);
   Base* test = new Exe(cmd);

   EXPECT_NE(test->execute(), 0);
}

TEST(TestFlagF, RegularFile) {
    string input = "test -f rshell";
    vector<string> cmd = parse(input);
    Base* test = new Exe(cmd);
    
    EXPECT_EQ(test->execute(), 0);
}

TEST(TestFlagF, NonRegularFile) {
    string input = "test -f src";
    vector<string> cmd = parse(input);
    Base* test = new Exe(cmd);

    EXPECT_NE(test->execute(), 0);
}

TEST(TestOutputRedirect, ls) {
    string input = "ls > file; echo append >> file";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestOutputRedirect, lsAll) {
    string input = "ls -a > file2; echo append2 >> file2";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestOutputRedirect, echo) {
    string input = "echo testing > file3; echo appendls >> file3; ls >> file3";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestInputRedirect, ls) {
    string input = "cat < file; rm file";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestInputRedirect, lsAll) {
    string input = "cat < file2; rm file2";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestInputRedirect, echo) {
    string input = "cat < file3; rm file3";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestPipe, grep) {
    string input = "ls -la | grep s";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestPipe, tr) {
    string input = "ls -la | tr A-Z a-z";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestPipe, mixedRedirectionPass) {
    string input = "ls < . | tr A-Z a-z | tee out1 | tr a-z A-Z > out2; rm out1; rm out2";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestPipe, mixedRedirectionFail) {
    string input = "ls > . | tr A-Z a-z | tee out1 | tr a-z A-Z > out2; rm out1; rm out2";
    vector<string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), -1);
}

#endif
