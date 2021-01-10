#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>
#include "../headers/Parser.h"
#include "../headers/Lexer.h"
#include "../headers/Token.h"

#include <iostream>

Parser::Parser(
  std::vector<Product> &&grammar,
  std::vector<StaticTokenDefinition> &&statics,
  std::vector<DynamicTokenDefinition> &&dynamics
) : Grammar(grammar), lexer(std::move(statics), std::move(dynamics))
{}
 
Parser::~Parser() { clear(); }

std::shared_ptr<Node> Parser::parse(std::string &source){
  m_tokens = lexer.tokenize(source);

  std::shared_ptr<Node> result(calc(Grammar[0].getType()));
  
  // +1 - index by tokens; parsing ended but last lexems ignored
  if (!hasError() && m_tokenId != m_tokens->size() - 1) setError("Unknown Error"); 
  if (hasError()) throw m_error;

  clear();
  return result;
}

std::shared_ptr<Node> Parser::calc(TokenType token) {
  if (hasError()) return nullptr;
  if (!isNonterminal(token))
    return std::make_shared<Node>(get());

  // memorization
  std::pair<int, TokenType> lockation{ m_tokenId, token }; 
  if (auto node(m_cache.find(lockation)); node != m_cache.end()) { // if in cache we have the same node
    setId(node->second.tokenId); // set id from memory
    setError(std::string(node->second.error)); // set error from memory
    return node->second.node; // return node from memory
  }

  get(); // shift be one to get correct now()
  auto eqs(getProd(token)->getEqualents()); 
  std::vector<std::shared_ptr<Node>> stack {};
  const std::vector<TokenType>* eq { getEq(eqs) };

  if (!eq && !hasError())
    setError("Unexpected token \"" + now()->getValue() + std::string("\" at ") + std::to_string(now()->getOffset()));

  if(eq) setId(m_tokenId - 1); // if has error not do step back
  for (int i(0); eq && !hasError() && i < eq->size(); ++i)
    stack.push_back(calc(eq->at(i)));

  // if has error return nullptr, else create new node from stack
  std::shared_ptr<Node> result { hasError() ? nullptr : std::make_shared<Node>(token, stack) }; 
  memorize(lockation, LockationData{result, m_error, m_tokenId}); // memorize
  return result;
}

bool Parser::isCorrect(std::vector<TokenType> &eqs) {
  auto checkLookahead ( [&](){
    return ( eqs.size() == 1 /* dont need lookahead */ ||
    hasEpsilon(eqs[1]) /* epsilon allways true */ || 
    peek() && (eqs[1] == peek()->getType()) /* lookahead is correct */ || 
    peek() && isNonterminal(eqs[1]) /* cannot check lookahead -> true cus this has LL(1) grammar */);
  }); // lol, js

  if (eqs.empty()) return true; // is epsilon, allways true
  if (!now()) return false; // no tokens
  if (!isNonterminal(eqs[0])) // simple check for terminal symbols
    return eqs[0] == now()->getType() && checkLookahead();

  int memId { m_tokenId }; // store id
  setId(m_tokenId - 1); // step back
  calc(eqs[0]); // calc first node of eqs
  bool res { !hasError() && checkLookahead() }; // if calc was succesful check lookahead and get result
  setError(""); // erase all errors, errors will be in the cycle of evaluation
  setId(memId); // restore token id as nothing happend
  return res; // return
}

const std::vector<TokenType> *Parser::getEq(std::vector<std::vector<TokenType>> &eqs) {
  for (int i(0); i < eqs.size(); ++i) // check all equalts
    if (isCorrect(eqs[i]))
      return &eqs[i];

  return nullptr;
}

const Token* Parser::now() const {
  if (m_tokenId >= static_cast<int>(m_tokens->size())) return nullptr;
  return m_tokens->at(m_tokenId);
}

const Token* Parser::peek() const {
  if (m_tokenId + 1 >= static_cast<int>(m_tokens->size())) return nullptr;
  return m_tokens->at(m_tokenId + 1);
}

const Token* Parser::get(){
  ++m_tokenId;
  return now();
}

const Product * Parser::getProd(TokenType token) const {
  auto prod = std::find_if(Grammar.begin(), Grammar.end(),
      [token](Product prod) -> bool { return prod.getType() == token; });
  if (prod == Grammar.end()) return nullptr;
  return &*prod;
}

bool Parser::isNonterminal(TokenType token) const {
  return getProd(token);
}

bool Parser::hasEpsilon(TokenType token) const {
  const Product* prod { getProd(token) };

  return prod && 
    0 != std::count_if(prod->getEqualents().begin(), prod->getEqualents().end(), 
        [](auto el) { return el.size() == 0; });
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
