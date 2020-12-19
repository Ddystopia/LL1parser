#include "../headers/Token.h"
#include <string>
#include <regex>


Token::Token(TokenType type, std::string value)
  : m_type(type), m_value(value)
{}

template <class T>
TokenDefinition<T>::TokenDefinition(T repres, TokenType type)
  : m_represantation(repres), m_type(type)
{}


StaticTokenDefinition::StaticTokenDefinition(std::string repres, TokenType type)
  : TokenDefinition<std::string>(repres, type)
{}


DynamicTokenDefinition::DynamicTokenDefinition(std::string repres, TokenType type)
  : TokenDefinition<std::regex>(std::regex(repres), type) 
{}

TokenType::TokenType(std::string type)
  : m_type(type)
{}

bool operator==(const TokenType &left, const TokenType &right) {
  return left.getType() == right.getType();
}

bool operator!=(const TokenType &left, const TokenType &right){
  return left.getType() != right.getType();
}

Product::Product(TokenType type, 
  std::initializer_list<std::initializer_list<TokenType>> eqS)
  : m_type(type), m_equalentSeries(std::vector<std::vector<TokenType>>())
{
  for (auto eqs = eqS.begin(); eqs != eqS.end(); eqs++) {
    m_equalentSeries.push_back(std::vector<TokenType>(*eqs));
  }
}

