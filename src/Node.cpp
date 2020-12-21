#include <vector>
#include "../headers/Token.h"
#include "../headers/Node.h"

Node::Node(const Token *token)
  : m_type(token->getType()), m_value(token->getValue())
{}

Node::Node(TokenType type, const std::vector<Node *> &subnodes)
  : m_type(type), m_subnodes(subnodes)
{}

