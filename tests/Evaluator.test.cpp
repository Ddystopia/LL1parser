#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include "../headers/Parser.h"
#include "../headers/Evaluator.h"

// Non-terminals
const TokenType EXPR = TokenType("EXPR");
const TokenType EXPR2 = TokenType("EXPR'");
const TokenType TERM = TokenType("TERM");
const TokenType TERM2 = TokenType("TERM'");
const TokenType POW = TokenType("POW");
const TokenType POW2 = TokenType("POW'");
const TokenType FACT = TokenType("FACT");
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

Parser parserEv { 
  {
    { EXPR, {
      { TERM, EXPR2 }
    } },
    { EXPR2, {
      { PLUS, TERM, EXPR2 }, { MINUS, TERM, EXPR2 }, {}
    } },
    { TERM, {
      { POW, TERM2 }
    } }, 
    { TERM2, {
      { STAR, POW, TERM2 }, { SLASH, POW, TERM2 }, {}
    } }, 
    { POW, {
      { FACT }, { FACT, POWER, POW }
    } },
    { FACT, {
      { NUM }, { LP, EXPR, RP }, { MINUS, FACT }, { PLUS, FACT },
    } },
  },
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


Evaluator evaluator;

TEST(EvalTests, NumEval) {
  std::string input("1");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, 1);
}

TEST(EvalTests, PlusSimpleEval) {
  std::string input("1+1");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, 1+1);
}

TEST(EvalTests, UnatySimpleEval) {
  std::string input("1--1");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, 1-(-1));
}

TEST(EvalTests, MulAndMinusSimpleEval) {
  std::string input("15-2*3");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, 15-2*3);
}

TEST(EvalTests, PowerEval) {
  std::string input("2^2^3");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, std::pow(2, std::pow(2, 3)));
}

TEST(EvalTests, BracketsTest) {
  std::string input("(15-2)*3");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, (15-2)*3);
}

TEST(EvalTests, AllOpersTest) {
  std::string input("15*3/4*(3+4*2^2)-8*1");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, 15.0*3/4*(3+4*std::pow(2, 2))-8*1);
}
