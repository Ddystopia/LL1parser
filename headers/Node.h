#ifndef NODE
#define NODE

#include <vector>
#include <string>
#include "../headers/Token.h"

class Node {
  private: 
    std::string m_value{""};
    TokenType m_type;
    std::vector<Node *> m_subnodes{};
  public: 
    Node(const Token* token);
    Node(TokenType type, const std::vector<Node *> &subnodes);
    TokenType getType() const { return m_type; };
    const std::string &getValue() const { return m_value; };
    const std::vector<Node *> &getSubnodes() const { return m_subnodes; }
};

#endif
