#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include "../headers/Lexer.h"
#include "../headers/Token.h"

Lexer::Lexer(
  std::vector<StaticTokenDefinition> &&statics, 
  std::vector<DynamicTokenDefinition> &&dynamics
) : statics(statics), dynamics(dynamics)
{}
 
std::vector<Token*> *Lexer::tokenize(const std::string &source){
  auto lexems { new std::vector<Token*> };
  lexems->reserve(source.length()); // wont be bigger then source 
  m_source = source;

  skipSpaces();
  while(inBounds()){
    Token *token;
    Token *staticTry(staticToken());

    token = staticTry ? staticTry : dynamicToken();
    if(!token) 
      throw std::string("Unexpected char ") + m_source[m_offset] + " at " + std::to_string(m_offset + 1);

    lexems->push_back(token);
    skipSpaces();
  }

  cleanUp();
  return lexems;
}

Token* Lexer::staticToken(){
  for(auto const &tokenDef: statics) {
    std::string rep(tokenDef.getRepres());

    if(m_source.substr(m_offset, rep.length()) != rep)
      continue;

    m_offset += rep.length();

    return new Token(tokenDef.getType(), rep, m_offset);
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

    return new Token(tokenDef.getType(), value, m_offset);
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
