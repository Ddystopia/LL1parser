#ifndef NODE
#define NODE

#include <vector>
#include "../headers/Token.h"

class Node {
  protected: 
    std::string m_value{""};
    TokenType m_type;
    std::vector<Node *> m_subnodes{};
  public: 
    Node(const Token* token);
    Node(TokenType type, const std::vector<Node *> &subnodes);
    TokenType getType() const { return m_type; };
    std::string getValue() const { return m_value; };
};

#endif
