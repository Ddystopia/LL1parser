#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>
#include "../headers/Parser.h"
#include "../headers/Lexer.h"
#include "../headers/Token.h"

#include <iostream>

Parser::Parser() {}
Parser::~Parser() { clear(); }

std::shared_ptr<Node> Parser::parse(const std::string &source){
  using TokenDefinitions::Grammar;

  Lexer lexer{Lexer()};
  m_tokens = lexer.tokenize(source);

  std::shared_ptr<Node> result(calc(Grammar[0].getType(), m_tokens->size() - 2));
  
  // +1 - index by tokens + EOI, -1 - get last index
//   if (m_tokenId != m_tokens->size() - 2) setError("someSize");
  if (m_error.size() != 0) throw m_error;

  clear();
  return result;
}

std::shared_ptr<Node> Parser::calc(TokenType token, int expectedEndId) {
  // memorization
  std::pair<int, TokenType> lockation{ m_tokenId, token }; 
  if (auto node(m_cache.find(lockation)); node != m_cache.end()) { 
    setId(node->second.second);
    return node->second.first;
  }

  const Product *prod(Product::getProd(token));
  const std::vector<std::vector<TokenType>> &eqs(prod->getEqualents());
  std::shared_ptr<Node> result { nullptr };
  int startTokenId(m_tokenId);

  for (int i(0); i < eqs.size(); ++i) {
    std::vector<std::shared_ptr<Node>> stack{};

    for (auto const &token: eqs[i]) {
      std::shared_ptr<Node> node; 
      if (peek()->getType() != token) { 
        if(!token.isProduct()) break;
        std::shared_ptr<Node> tmpNode(calc(token, eqs[i].size() == 1 ? expectedEndId : -1));
        if (!tmpNode) {
          if (i == eqs.size() - 1) break;
          setError("");
        }
        node = tmpNode;
      }
      stack.push_back(node ? node : std::make_shared<Node>(get()));
    }

    if (stack.size() == eqs[i].size() && (expectedEndId == -1 || expectedEndId == m_tokenId)) { 
      result = std::make_shared<Node>(token, stack);
      break;
    }

    setId(startTokenId); 
  }

  if (!result && m_error.size() == 0)
    setError("Unexpected token " + peek()->getValue() + std::string(" at ") + std::to_string( peek()->getOffset() ));

  memorize(lockation, std::make_pair(result, m_tokenId));
  return result;
}

const Token* Parser::peek(){
  return m_tokens->at(m_tokenId + 1);
}

const Token* Parser::get(){
  return m_tokens->at(++m_tokenId);
}

void Parser::memorize(
    std::pair<int, TokenType> lockation, 
    std::pair<std::shared_ptr<Node>, int> data) 
{
  m_cache.insert(std::make_pair(lockation, data));
}

void Parser::clear(){
  setId(-1);
  m_cache.clear();
  setError("");

  if (!m_tokens) return;
  for (auto it = m_tokens->begin(); it != m_tokens->end(); it++) 
    delete *it;
  delete m_tokens;
  m_tokens = nullptr;
}

