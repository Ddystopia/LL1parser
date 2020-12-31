#include "../headers/Token.h"
#include <string>
#include <regex>
#include <algorithm>

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

bool TokenType::isProduct() const {
  using TokenDefinitions::Grammar;
  auto prod = std::find_if(Grammar.begin(), Grammar.end(), 
      [this](Product &prod) -> bool { return prod.getType() == *this; });

  return prod != Grammar.end();
}

bool operator==(const TokenType &left, const TokenType &right) {
  return left.getType() == right.getType();
}

bool operator!=(const TokenType &left, const TokenType &right){
  return left.getType() != right.getType();
}

bool operator<(const TokenType &left, const TokenType &right){
  return left.getType() < right.getType();
}

Product::Product(TokenType type, 
  std::initializer_list<std::initializer_list<TokenType>> eqS)
  : m_type(type), m_equalentSeries(std::vector<std::vector<TokenType>>())
{
  for (auto eqs(eqS.begin()); eqs != eqS.end(); eqs++) {
    m_equalentSeries.push_back(std::vector<TokenType>(*eqs));
  }

  std::sort(m_equalentSeries.begin(), m_equalentSeries.end(), 
      [](const std::vector<TokenType> &a, const std::vector<TokenType> &b) -> bool {
    return a.size() > b.size(); 
  });
}

const Product *Product::getProd(TokenType token) {
  using TokenDefinitions::Grammar;
  return &*std::find_if(Grammar.begin(), Grammar.end(),
      [token](Product prod) -> bool { return prod.getType() == token; });
}


