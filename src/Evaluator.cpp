#include <vector>
#include <string>
#include <cmath>
#include <memory>
#include <string>
#include "../headers/Evaluator.h"
#include "../headers/Node.h"
#include "../headers/Token.h"

#include <iostream>

long double Evaluator::eval(std::shared_ptr<Node> node) {
  if (node->getSubnodes().size() == 1) return eval(node->getSubnodes()[0]);
  if (node->getType() == TokenType("NUM")) return stold(node->getValue());

  TokenType oper { node->getSubnodes()[1]->getType() };

  if (oper == TokenType("PLUS")) return eval(node->getSubnodes()[0]) + eval(node->getSubnodes()[2]);
  if (oper == TokenType("MINUS")) return eval(node->getSubnodes()[0]) - eval(node->getSubnodes()[2]);
  if (oper == TokenType("STAR")) return eval(node->getSubnodes()[0]) * eval(node->getSubnodes()[2]);
  if (oper == TokenType("SLASH")) return eval(node->getSubnodes()[0]) / eval(node->getSubnodes()[2]);
  if (oper == TokenType("POWER")) return std::pow(eval(node->getSubnodes()[0]), eval(node->getSubnodes()[2]));
  if (node->getType() == TokenType("FACT")) return eval(node->getSubnodes()[1]);

  throw std::string("Cannot evaluate");
}



