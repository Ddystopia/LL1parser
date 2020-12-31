#include "../headers/Evaluator.h"
#include "../headers/Node.h"
#include "../headers/Token.h"
#include <vector>
#include <string>

long double Evaluator::eval(Node *node) {
  if (node->getSubnodes().size() == 1) return eval(node->getSubnodes()[0]);
  if (node->getType() == TokenType("NUM")) return stold(node->getValue());
}


