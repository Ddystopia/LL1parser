#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <memory>
#include <map>
#include <string>
#include <functional>
#include "../headers/Evaluator.h"
#include "../headers/Node.h"
#include "../headers/Token.h"

#include <iostream>

#define MATH_FUNC(name, fn) \
  { (name), [](long double number) { return (fn); } }

std::map<std::string, std::function<long double(long double)>> functions {
  MATH_FUNC("sin", std::sin(number)),
  MATH_FUNC("cos", std::cos(number)),
  MATH_FUNC("tan", std::tan(number)),
  MATH_FUNC("cot", 1/std::tan(number)),
  MATH_FUNC("ctg", 1/std::tan(number)),
  MATH_FUNC("arcsin", std::asin(number)),
  MATH_FUNC("asin", std::asin(number)),
  MATH_FUNC("arccos", std::acos(number)),
  MATH_FUNC("acos", std::acos(number)),
  MATH_FUNC("arctan", std::atan(number)),
  MATH_FUNC("atan", std::atan(number)),
  MATH_FUNC("arccot", M_PI_2 - std::atan(number)),
  MATH_FUNC("acot", M_PI_2 - std::atan(number)),
  MATH_FUNC("arcctg", M_PI_2 - std::atan(number)),
  MATH_FUNC("actg", M_PI_2 - std::atan(number)),
};

#define CALC_SUBS(type1, op1, op2) {\
    long double result { eval(subs[0]) };\
    std::shared_ptr<Node> node { subs[1] };\
 \
    while (node->getSubnodes().size() != 0) {\
      if (node->getSubnodes()[0]->getType() == TokenType(type1)) \
        result = result op1 eval(node->getSubnodes()[1]);\
      else result = result op2 eval(node->getSubnodes()[1]);\
\
      node = node->getSubnodes()[2];\
    }\
\
    return result;\
  } 
 
long double Evaluator::eval(std::shared_ptr<Node> node) {
  std::vector<std::shared_ptr<Node>> subs { node->getSubnodes() };

  if (node->getType() == TokenType("NUM")) return stold(node->getValue());
  if (node->getType() == TokenType("FACT") && subs[0]->getType() == TokenType("LP")) return eval(node->getSubnodes()[1]);
  if (node->getType() == TokenType("FACT") && subs[0]->getType() == TokenType("MINUS")) return -eval(subs[1]);
  if (node->getType() == TokenType("FACT") && subs[0]->getType() == TokenType("PLUS")) return +eval(subs[1]);
  if (node->getType() == TokenType("FACT") && subs[0]->getType() == TokenType("WORD")) {
    auto fn { functions.find(subs[0]->getValue()) };
    if (fn == functions.end()) throw std::string("Unknown function \"" + subs[0]->getValue() + "\"");
    return fn->second(eval(subs[2]));
  }

  if (subs.size() == 1) return eval(subs[0]);
  if (subs[1]->getSubnodes().size() == 0 && subs.size() == 2) return eval(subs[0]);
 
  if (node->getType() == TokenType("EXPR")) CALC_SUBS("PLUS", +, -)
  if (node->getType() == TokenType("TERM")) CALC_SUBS("STAR", *, /)

  if (node->getType() == TokenType("POW")) return std::pow(eval(subs[0]), eval(subs[2]));

  throw std::string("Cannot evaluate");
}

