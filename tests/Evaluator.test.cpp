#include <gtest/gtest.h>
#include <string>
#include "../headers/Parser.h"
#include "../headers/Evaluator.h"

Evaluator evaluator;
Parser parserEv;

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

TEST(EvalTests, BracketsTest) {
  std::string input("(15-2)*3");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, (15-2)*3);
}

TEST(EvalTests, AllOpersTest) {
  std::string input("15*3/4*(3+4*2)-8*1");
  long double result { evaluator.eval(parserEv.parse(input)) };

  ASSERT_EQ(result, 15.0*3/4*(3+4*2)-8*1);
}
