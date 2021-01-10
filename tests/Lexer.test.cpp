#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../headers/Lexer.h"
#include "../headers/Token.h"

// Terminals
const TokenType PLUS = TokenType("PLUS");
const TokenType MINUS = TokenType("MINUS");
const TokenType STAR = TokenType("STAR");
const TokenType SLASH = TokenType("SLASH");
const TokenType LP = TokenType("LP");
const TokenType RP = TokenType("RP");
const TokenType POWER = TokenType("POWER");
const TokenType NUM = TokenType("NUM");
const TokenType WORD = TokenType("WORD");

Lexer lexer { 
  {
    { "+", PLUS },
    { "-", MINUS },
    { "*", STAR },
    { "/", SLASH },
    { "(", LP },
    { ")", RP },
    { "^", POWER },
  },
  {
    { "[0-9]+(\\.[0-9]+)?", NUM },
    //DynamicTokenDefinition("[a-zA-Z_][a-zA-Z_-?]*", WORD),
  }  
};

// i know about memory leacks but it isnt important here

TEST(LexerTests, PLUSTokenTokenizesCorrectly) {
  std::string addSymbol("+");
  std::vector<Token*> tokens(*lexer.tokenize(addSymbol));

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0]->getType(), TokenType("PLUS"));
}

TEST(LexerTests, NUMTokenTokenizesCorrectly) {
  std::string numSymbol("11");
  std::vector<Token*> tokens(*lexer.tokenize(numSymbol));

  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0]->getType(), TokenType("NUM"));
  ASSERT_EQ(tokens[0]->getValue(), "11");
}

TEST(LexerTests, SimpleExpressionTokenizesCorrectly) {
  std::string expression("12-1");
  std::vector<Token*> tokens(*lexer.tokenize(expression));

  ASSERT_EQ(tokens.size(), 3);

  ASSERT_EQ(tokens[0]->getType(), TokenType("NUM"));
  ASSERT_EQ(tokens[0]->getValue(), "12");

  ASSERT_EQ(tokens[1]->getType(), TokenType("MINUS"));

  ASSERT_EQ(tokens[2]->getType(), TokenType("NUM"));
  ASSERT_EQ(tokens[2]->getValue(), "1");
}

TEST(LexerTests, SimpleExpressionWithSpacesTokenizesCorrectly) {
  std::string expression("12 - 1");
  std::vector<Token*> tokens(*lexer.tokenize(expression));

  ASSERT_EQ(tokens.size(), 3);

  ASSERT_EQ(tokens[0]->getType(), TokenType("NUM"));
  ASSERT_EQ(tokens[0]->getValue(), "12");

  ASSERT_EQ(tokens[1]->getType(), TokenType("MINUS"));

  ASSERT_EQ(tokens[2]->getType(), TokenType("NUM"));
  ASSERT_EQ(tokens[2]->getValue(), "1");
}
