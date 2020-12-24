#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include "../headers/Lexer.h"
#include "../headers/Token.h"

using TokenDefinitions::statics;
using TokenDefinitions::dynamics;

const std::string EOI{"EOI"};

Lexer::Lexer() {}

std::vector<Token*> *Lexer::tokenize(const std::string &source){
  auto lexems{new std::vector<Token*>};
  lexems->reserve(source.length() + 1); // wont be bigger then source + EOI
  m_source = source;

  skipSpaces();
  while(inBounds()){
    Token *token;
    Token *staticTry(staticToken());

    token = staticTry ? staticTry : dynamicToken();
    if(!token) throw "Unexpected char at {m_offset + 1}";

    lexems->push_back(token);
    skipSpaces();
  }

  lexems->push_back(new Token(TokenType(EOI), EOI)); // Exlution

  cleanUp();
  return lexems;
}

Token* Lexer::staticToken(){
  for(auto const &tokenDef: statics) {
    std::string rep(tokenDef.getRepres());

    if(m_source.substr(m_offset, rep.length()) != rep)
      continue;

    m_offset += rep.length();

    return new Token(tokenDef.getType(), rep);
  }
  return nullptr;
}

Token* Lexer::dynamicToken(){
  for(auto const &tokenDef: dynamics) {
    std::regex rep(tokenDef.getRepres());

    std::smatch m;
    std::string substr(m_source.substr(m_offset));

    if(!std::regex_search(substr, m, rep) || m.position(0) != 0) 
      continue;
    
    std::string value(m[0].str());
    m_offset += value.length();

    return new Token(tokenDef.getType(), value);
  }
  return nullptr;
}

void Lexer::skipSpaces(){
  while(inBounds() && 
      std::find(m_spaces.begin(), m_spaces.end(), m_source[m_offset]) != m_spaces.end()) 
    m_offset++;
}

bool Lexer::inBounds(){
  return m_offset < m_source.length();
}

void Lexer::cleanUp(){
  m_offset = 0;
}
