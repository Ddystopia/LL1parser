#ifndef NODE
#define NODE

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "../headers/Token.h"

class Node {
  private: 
    std::string m_value{""};
    TokenType m_type;
    std::vector<std::shared_ptr<Node>> m_subnodes{};
  public: 
    Node(const Token* token);
    Node(TokenType type, const std::vector<std::shared_ptr<Node>> &subnodes);
    TokenType getType() const { return m_type; };
    const std::string &getValue() const { return m_value; };
    const std::vector<std::shared_ptr<Node>> &getSubnodes() const { return m_subnodes; }
    void reverseSubnodes() { std::reverse(m_subnodes.begin(), m_subnodes.end()); };
};

#endif
