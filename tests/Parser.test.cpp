#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../headers/Parser.h"
#include "../headers/Token.h"
#include "../headers/Node.h"

#include <iostream>

Parser parser(Parser{});

TEST(ParserTests, NUMParsesCorrectly) {
  std::string input("1");
  Node *AST(parser.parse(input));

  ASSERT_EQ(AST->getType(), TokenType("EXPR"));
  Node *numNode{AST->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]};
  ASSERT_EQ(numNode->getType(), TokenType("NUM"));
  ASSERT_EQ(numNode->getValue(), "1");
}

TEST(ParserTests, SimpleExprParce) {
  std::string input("1+1");
  Node *AST(parser.parse(input));

  ASSERT_EQ(AST->getType(), TokenType("EXPR"));
  ASSERT_EQ(AST->getSubnodes().size(), 3);
  ASSERT_EQ(AST->getSubnodes()[1]->getType(), TokenType("PLUS"));
  ASSERT_EQ(AST->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]->getValue(), "1");
  ASSERT_EQ(AST->getSubnodes()[2]->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]->getValue(), "1");
}

TEST(ParserTests, SimpleExprWothBrackets) {
  std::string input("1+(3*2)");
  Node *AST(parser.parse(input));

  ASSERT_EQ(AST->getType(), TokenType("EXPR"));
  ASSERT_EQ(AST->getSubnodes().size(), 3);
  ASSERT_EQ(AST->getSubnodes()[1]->getType(), TokenType("PLUS"));
  ASSERT_EQ(AST->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]->getValue(), "1");

  Node *inBrackets(AST->getSubnodes()[2]->getSubnodes()[0]->getSubnodes()[0]->getSubnodes()[0]);

  ASSERT_EQ(inBrackets->getType(), TokenType("FACT"));
  ASSERT_EQ(inBrackets->getSubnodes()[0]->getValue(), "(");
  ASSERT_EQ(inBrackets->getSubnodes()[1]->getType(), TokenType("EXPR"));
  ASSERT_EQ(inBrackets->getSubnodes()[2]->getValue(), ")");
}
