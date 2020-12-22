#include <string>
#include <vector>
#include <algorithm>
#include "../headers/Parser.h"
#include "../headers/Lexer.h"
#include "../headers/Token.h"

using TokenDefinitions::Grammar;

Parser::Parser()
  : m_tokenId(0), m_tokens(nullptr)
{}

Parser::~Parser() { clear(); }

Node* Parser::parse(const std::string &source){
  clear();
  Lexer lexer{Lexer()};
  m_tokens = lexer.tokenize(source);

  return calc(Grammar[0].getType());
}

Node* Parser::calc(TokenType token) {
  const Product *prod(getProd(token));
  std::vector<std::vector<TokenType>> eqs(prod->getEqualents());
  int startTokenId(m_tokenId);

  for (auto const &eq: eqs) {
    std::vector<Node *> stack{};

    for (auto const &token: eq) {
      if (peek()->getType() != token) { 
        if(token.isProduct()) stack.push_back(calc(token));
        else break;
      } else {
        stack.push_back(new Node(get()));
      }
    }

    if (stack.size() == eq.size()) 
      return new Node(token, stack);

    for (auto const &node: stack) delete node;
    setId(startTokenId); 
  }

  throw "some";
}

const Product *Parser::getProd(TokenType token) {
  return &*std::find_if(Grammar.begin(), Grammar.end(),
      [token](Product prod) -> bool { return prod.getType() == token; });
}

const Token* Parser::peek(){
  return (*m_tokens)[m_tokenId + 1];
}

const Token* Parser::get(){
  return (*m_tokens)[++m_tokenId];
}

void Parser::setId(int id){
  m_tokenId = id;
}

void Parser::clear(){
  setId(0);

  if (!m_tokens) return;
  for (auto it = m_tokens->begin(); it != m_tokens->end(); it++) 
    delete *it;
  delete m_tokens;
  m_tokens = nullptr;
}


