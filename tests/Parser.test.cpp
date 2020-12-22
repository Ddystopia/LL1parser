#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../headers/Parser.h"
#include "../headers/Token.h"
#include "../headers/Node.h"

Parser parser(Parser{});

TEST(ParserTests, NUMParsesCorrectly) {
  std::string input("1");
  Node *AST(parser.parse(input));

  ASSERT_EQ(AST->getType(), TokenType("EXPR"));
}
