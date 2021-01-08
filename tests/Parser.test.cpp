#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <string>
#include "../headers/Parser.h"
#include "../headers/Token.h"
#include "../headers/Node.h"

#include <iostream>

std::shared_ptr<Node> getSub(std::shared_ptr<Node> node, int depth) {
  std::shared_ptr<Node> result(node->getSubnodes()[0]);
  for (int i(1); i < depth; i++) result = result->getSubnodes().at(0);
  return result;
}

Parser parser;

TEST(ParserTests, NUMParsesCorrectly) {
  std::string input("1");
  std::shared_ptr<Node> AST(parser.parse(input));

  ASSERT_EQ(AST->getType(), TokenType("EXPR"));
  std::shared_ptr<Node> numNode{getSub(AST, 4)};
  ASSERT_EQ(numNode->getType(), TokenType("NUM"));
  ASSERT_EQ(numNode->getValue(), "1");
}

TEST(ParserTests, SimpleExprParce) {
  std::string input("1+1");
  std::shared_ptr<Node> AST(parser.parse(input));

  ASSERT_EQ(AST->getType(), TokenType("EXPR"));
  ASSERT_EQ(AST->getSubnodes().size(), 2);
  ASSERT_EQ(AST->getSubnodes()[1]->getType(), TokenType("EXPR'"));
  ASSERT_EQ(getSub(AST, 4)->getValue(), "1");
  ASSERT_EQ(getSub(AST->getSubnodes()[1]->getSubnodes()[1], 3)->getValue(), "1");
}

TEST(ParserTests, SimpleExprWithBrackets) {
  std::string input("1-(3/2)");
  std::shared_ptr<Node> AST(parser.parse(input));

  ASSERT_EQ(AST->getType(), TokenType("EXPR"));
  ASSERT_EQ(AST->getSubnodes().size(), 2);
  ASSERT_EQ(AST->getSubnodes()[1]->getSubnodes()[0]->getType(), TokenType("MINUS"));
  ASSERT_EQ(getSub(AST, 4)->getValue(), "1");

std::shared_ptr<Node> inBrackets(getSub(AST->getSubnodes()[1]->getSubnodes()[1], 2));

std::cout << inBrackets->getType().getStrType();
  ASSERT_EQ(inBrackets->getType(), TokenType("FACT"));
  ASSERT_EQ(inBrackets->getSubnodes()[0]->getValue(), "(");
  ASSERT_EQ(inBrackets->getSubnodes()[1]->getType(), TokenType("EXPR"));
  ASSERT_EQ(inBrackets->getSubnodes()[2]->getValue(), ")");
}
