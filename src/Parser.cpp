#include <string>
#include <vector>
#include "../headers/Parser.h"
#include "../headers/Lexer.h"
#include "../headers/Token.h"

typedef long double ld;

Parser::Parser()
  : m_tokenId(0), m_tokens(nullptr)
{}

ld Parser::parse(std::string source){
  Lexer lexer{Lexer()};
  m_tokens = lexer.tokenize(source);

  ld result(calc());
  clear();
  return result;
}

ld Parser::calc(){
  return expr();
}

ld Parser::expr(){
  ld result(0.0);
  int index(0);
  bool hasMatch(false);
  for (auto const &serie: TokenDefinitions::Grammar[0].getEqualents()) {
    if (peek()->getType() == serie[index]){
      get();
      index++;
      hasMatch = true;
    }
  }
  return result;
}

Token* Parser::peek(){
  return (*m_tokens)[m_tokenId + 1];
}

Token* Parser::get(){
  return (*m_tokens)[++m_tokenId];
}

void Parser::setId(int id){
  m_tokenId = id;
}

void Parser::clear(){
  setId(0);
  for (auto it = m_tokens->begin(); it != m_tokens->end(); it++) 
    delete *it;
  delete m_tokens;
  m_tokens = nullptr;
}


