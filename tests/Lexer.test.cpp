#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../headers/Lexer.h"

// i know about memory leacks but it isnt important here

Lexer lexer = Lexer();

TEST(LexerTests, PLUSTokenTokenizesCorrectly){
  std::string addSymbol("+");
  std::vector<Token*> tokens(*lexer.tokenize(addSymbol));

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0]->getType(), TokenTypes::PLUS);
}

TEST(LexerTests, NUMTokenTokenizesCorrectly){
  std::string numSymbol("11");
  std::vector<Token*> tokens(*lexer.tokenize(numSymbol));

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0]->getType(), TokenTypes::NUM);
  ASSERT_EQ(tokens[0]->getValue(), "11");
}

TEST(LexerTests, SimpleExpressionTokenizesCorrectly){
  std::string expression("12-1");
  std::vector<Token*> tokens(*lexer.tokenize(expression));

  ASSERT_EQ(tokens.size(), 3);

  ASSERT_EQ(tokens[0]->getType(), TokenTypes::NUM);
  ASSERT_EQ(tokens[0]->getValue(), "12");

  ASSERT_EQ(tokens[1]->getType(), TokenTypes::MINUS);

  ASSERT_EQ(tokens[2]->getType(), TokenTypes::NUM);
  ASSERT_EQ(tokens[2]->getValue(), "1");
}
