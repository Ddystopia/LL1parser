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
  ld result(0.0);

  Lexer lexer{Lexer()};
  m_tokens = lexer.tokenize(source);

    


  clear();
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


