#include <vector>
#include <cmath>
#include <memory>
#include <string>
#include "../headers/Evaluator.h"
#include "../headers/Node.h"
#include "../headers/Token.h"

long double Evaluator::eval(std::shared_ptr<Node> node) {
  if (node->getSubnodes().size() == 1) return eval(node->getSubnodes()[0]);

  if (node->getType() == TokenType("NUM")) return stold(node->getValue());
  if (node->getType() == TokenType("SUM")) return eval(node->getSubnodes()[0]) + eval(node->getSubnodes()[2]);
  if (node->getType() == TokenType("DER")) return eval(node->getSubnodes()[0]) - eval(node->getSubnodes()[2]);
  if (node->getType() == TokenType("MUL")) return eval(node->getSubnodes()[0]) * eval(node->getSubnodes()[2]);
  if (node->getType() == TokenType("DIV")) return eval(node->getSubnodes()[0]) / eval(node->getSubnodes()[2]);
  if (node->getType() == TokenType("POW")) return std::pow(eval(node->getSubnodes()[0]), eval(node->getSubnodes()[2]));
  if (node->getType() == TokenType("FACT")) return eval(node->getSubnodes()[1]);

  throw "Cannot evaluate";
}



