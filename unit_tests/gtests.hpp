#ifndef __GTESTS_HPP__
#define __GTESTS_HPP__

#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "../src/base.hpp"
#include "../src/connectorand.hpp"
#include "../src/connectoror.hpp"
#include "../src/connectorpipe.hpp"
#include "../src/connectorsemicolon.hpp"
#include "../src/exe.hpp"
#include "../src/nightmare.hpp"
#include "../src/parser.hpp"
#include "../src/test.hpp"

TEST(ExeTest, ExeFail)
{
    std::vector<std::string> cmd = {"memememememememe"}; //nonexistent cmommand
    Base* exe = new Exe(cmd);
    EXPECT_EQ(exe->execute(), -1);
}

TEST(ExeTest, ExePass)
{
    std::vector<std::string> cmd = {"ls"};
    Base* exe = new Exe(cmd);
    EXPECT_EQ(exe->execute(), 0);
}

TEST(ConnectTestAnd, Fail) 
{
    std::vector<std::string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    std::vector<std::string> cmd2;
    cmd2.push_back("ls");

    Base* exe = new Exe(cmd);
    Base* exe2 = new Exe(cmd2);

    Base* connect = new ConnectorAnd(exe, exe2);

    EXPECT_EQ(connect->execute(), -1);
}

TEST(ConnectTestAnd, Pass) 
{
    std::vector<std::string> cmd;
    cmd.push_back("echo");
    cmd.push_back("hello");

    std::vector<std::string> cmd2;
    cmd2.push_back("ls");

    Base* exe = new Exe(cmd);
    Base* exe2 = new Exe(cmd2);

    Base* connect = new ConnectorAnd(exe, exe2);

    EXPECT_EQ(connect->execute(), 0);
}

TEST(ConnectTestOr, Fail) 
{
    std::vector<std::string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    Base* exe = new Exe(cmd);

    Base* connect = new ConnectorOr(exe, exe);

    EXPECT_EQ(connect->execute(), -1);
}

TEST(ConnectTestOr, Pass) 
{
    std::vector<std::string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    std::vector<std::string> cmd2;
    cmd2.push_back("ls");

    Base* exe = new Exe(cmd);
    Base* exe2 = new Exe(cmd2);

    Base* connect = new ConnectorOr(exe, exe2);

    EXPECT_EQ(connect->execute(), 0);
}

TEST(ConnectTestSemicolon, Fail) 
{
    std::vector<std::string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    Base* exe = new Exe(cmd);

    Base* connect = new ConnectorSemicolon(exe, exe);

    EXPECT_EQ(connect->execute(), -1);
}

TEST(ConnectTestSemicolon, Pass) 
{
    std::vector<std::string> cmd;
    cmd.push_back("ls");
    cmd.push_back("nonsense");

    std::vector<std::string> cmd2;
    cmd2.push_back("echo");
    cmd2.push_back("plzwork");

    Base* exe = new Exe(cmd);
    Base* exe2 = new Exe(cmd2);

    Base* connect = new ConnectorSemicolon(exe, exe);
    Base* connect2 = new ConnectorSemicolon(connect, exe2);

    EXPECT_EQ(connect2->execute(), 0);
}

TEST(ParenthesesTest, LeftSide) 
{
    std::string input = "(echo a && echo b) && echo c";
    std::vector<std::string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    EXPECT_EQ(exe->execute(), 0);

}

TEST(ParenthesesTest, RightSide) 
{
    std::string input = "echo a && (echo b && echo c)";
    std::vector<std::string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    EXPECT_EQ(exe->execute(), 0);
}

TEST(ParenthesesTest, BothSides) 
{
    std::string input = "(echo a && echo b) && (echo c && echo d)";
    std::vector<std::string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    EXPECT_EQ(exe->execute(), 0);
}

TEST(ParenthesesTest, Whole) 
{
    std::string input = "(echo a && echo b && echo c && echo d)";
    std::vector<std::string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    EXPECT_EQ(exe->execute(), 0);
}

TEST(ParenthesesTest, Layered) 
{
    std::string input = "((((echo a))))";
    std::vector<std::string> cmd = parse(input);

    Base* exe = nightmare(cmd);

    EXPECT_EQ(exe->execute(), 0);
}

TEST(TestFlagE, ExistingFile) 
{
    std::string input = "test -e src";
    std::vector<std::string> cmd = parse(input);
    Base* test = new Exe(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestFlagE, NonExistingFile) 
{
   std::string input = "test -e meme";
   std::vector<std::string> cmd = parse(input);
   Base* test = new Exe(cmd);

   EXPECT_NE(test->execute(), 0);
}

TEST(TestFlagD, IsDirectory) 
{
   std::string input = "test -d src";
   std::vector<std::string> cmd = parse(input);
   Base* test = new Exe(cmd);

   EXPECT_EQ(test->execute(), 0);
}

TEST(TestFlagD, IsNotDirectory) 
{
   std::string input = "test -d CMakeLists.txt";
   std::vector<std::string> cmd = parse(input);
   Base* test = new Exe(cmd);

   EXPECT_NE(test->execute(), 0);
}

TEST(TestFlagF, RegularFile) 
{
    std::string input = "test -f rshell";
    std::vector<std::string> cmd = parse(input);
    Base* test = new Exe(cmd);
    
    EXPECT_EQ(test->execute(), 0);
}

TEST(TestFlagF, NotRegularFile) 
{
    std::string input = "test -f src";
    std::vector<std::string> cmd = parse(input);
    Base* test = new Exe(cmd);

    EXPECT_NE(test->execute(), 0);
}

TEST(TestOutputRedirect, ls) 
{
    std::string input = "ls > file; echo append >> file; rm file";
    std::vector<std::string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestOutputRedirect, lsAll) 
{
    std::string input = "ls -a > file2; echo append2 >> file2; rm file2";
    std::vector<std::string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestOutputRedirect, echo) 
{
    std::string input = "echo testing > file3; echo appendls >> file3; ls >> file3; rm file3";
    std::vector<std::string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestInputRedirect, cat) 
{
    std::string input = "touch file; cat < file; rm file";
    std::vector<std::string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestPipe, grep) 
{
    std::string input = "ls -la | grep s";
    std::vector<std::string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestPipe, tr) 
{
    std::string input = "ls -la | tr A-Z a-z";
    std::vector<std::string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestPipe, MixedRedirectionPass) 
{
    std::string input = "ls < . | tr A-Z a-z | tee out1 | tr a-z A-Z > out2; rm out1; rm out2";
    std::vector<std::string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), 0);
}

TEST(TestPipe, MixedRedirectionFail) 
{
    std::string input = "ls > . | tr A-Z a-z | tee out1 | tr a-z A-Z > out2; rm out1; rm out2";
    std::vector<std::string> cmd = parse(input);
    Base* test = nightmare(cmd);

    EXPECT_EQ(test->execute(), -1);
}

#endif // __GTESTS_HPP__
