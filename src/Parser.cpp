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

  Lexer lexer;
  m_tokens = lexer.tokenize(source);

  std::shared_ptr<Node> result(calc(Grammar[0].getType()));
  
  // +1 - index by tokens + EOI, -1 - get last index
  if (m_tokenId != m_tokens->size() - 1) setError("Unknown Error");
  if (hasError()) throw m_error;

  clear();
  return result;
}

std::shared_ptr<Node> Parser::calc(TokenType token) {
  if (hasError()) return nullptr;
  if (!token.isProduct())
    return std::make_shared<Node>(get());

  // memorization
  std::pair<int, TokenType> lockation{ m_tokenId, token }; 
  if (auto node(m_cache.find(lockation)); node != m_cache.end()) { 
    setId(node->second.tokenId);
    setError(std::string(node->second.error));
    return node->second.node;
  }

  get();
  auto eqs(Product::getProd(token)->getEqualents());
  std::vector<std::shared_ptr<Node>> stack {};
  const std::vector<TokenType>* eq { getEq(eqs) };

  if (!eq && !hasError())
    setError("Unexpected token \"" + now()->getValue() + std::string("\" at ") + std::to_string(now()->getOffset()));

  if(eq) setId(m_tokenId - 1);
  for (int i(0); eq && !hasError() && i < eq->size(); ++i)
    stack.push_back(calc(eq->at(i)));

  std::shared_ptr<Node> result { hasError() ? nullptr : std::make_shared<Node>(token, stack) };
  memorize(lockation, LockationData{result, m_error, m_tokenId});
  return result;
}

bool Parser::isCorrect(std::vector<TokenType> eqs) {
  bool res = eqs[0] == now()->getType() ;
  bool res1 = eqs.size() == 1 || (peek() && (eqs[1] == peek()->getType() || eqs[1].isProduct()));
  if (eqs[0].isProduct()) {
    int memId { m_tokenId };
    setId(m_tokenId - 1);
    calc(eqs[0]);
    if (!hasError()) res = true;
    res1 = eqs.size() == 1 || (peek() && (eqs[1] == peek()->getType() || eqs[1].isProduct()));
    setError("");
    setId(memId);
  }

  return res && res1;
}

const std::vector<TokenType> *Parser::getEq(std::vector<std::vector<TokenType>> &eqs) {
  for (int i(0); i < eqs.size(); ++i)
    if (isCorrect(eqs[i]))
      return &eqs[i];

  return nullptr;
}

const Token* Parser::now(){
  return m_tokens->at(m_tokenId);
}

const Token* Parser::peek(){
  if (m_tokenId + 1 >= static_cast<int>(m_tokens->size())) return nullptr;
  return m_tokens->at(m_tokenId + 1);
}

const Token* Parser::get(){
  if (m_tokenId + 1 >= static_cast<int>(m_tokens->size())) return nullptr;
  return m_tokens->at(++m_tokenId);
}

void Parser::memorize(std::pair<int, TokenType> lockation, LockationData data) {
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
