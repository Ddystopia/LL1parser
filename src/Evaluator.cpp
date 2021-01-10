#include <vector>
#include <string>
#include <cmath>
#include <memory>
#include <string>
#include <functional>
#include "../headers/Evaluator.h"
#include "../headers/Node.h"
#include "../headers/Token.h"

#include <iostream>

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

  if (subs.size() == 1 || subs[1]->getSubnodes().size() == 0) return eval(subs[0]);
 
  if (node->getType() == TokenType("EXPR")) CALC_SUBS("PLUS", +, -)
  if (node->getType() == TokenType("TERM")) CALC_SUBS("STAR", *, /)

  if (node->getType() == TokenType("POW")) return std::pow(eval(subs[0]), eval(subs[1]));
  if (node->getType() == TokenType("POW'")) 
    return std::pow(eval(subs[1]), subs[2]->getSubnodes().size() > 0 ? eval(subs[2]) : 1);

  throw std::string("Cannot evaluate");
}

