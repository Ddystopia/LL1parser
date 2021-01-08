#include "../headers/Token.h"
#include <cassert>
#include <string>
#include <regex>
#include <algorithm>

Token::Token(TokenType type, std::string value, int offset)
  : m_type(type), m_value(value), m_offset(offset)
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

bool TokenType::isNonterminal() const {
  return Product::getProd(*this);
}

bool TokenType::hasEpsilon() const {
  const Product* prod { Product::getProd(*this) };

  return prod && 
    0 != std::count_if(prod->getEqualents().begin(), prod->getEqualents().end(), 
        [](auto el) { return el.size() == 0; });
}

bool operator==(const TokenType &left, const TokenType &right) {
  return left.m_type == right.m_type;
}

bool operator!=(const TokenType &left, const TokenType &right) {
  return left.m_type != right.m_type;
}

bool operator<(const TokenType &left, const TokenType &right) {
  return left.m_type < right.m_type;
}

Product::Product(TokenType type, 
  std::initializer_list<std::initializer_list<TokenType>> eqs)
  : m_type(type), m_equalentSeries(std::vector<std::vector<TokenType>>())
{
  for (auto const &eq: eqs) {
    m_equalentSeries.push_back(std::vector<TokenType>(eq));
  }

  std::sort(m_equalentSeries.begin(), m_equalentSeries.end(), 
      [](auto &a, auto &b) -> bool { return a.size() > b.size(); }
  );
}

const Product *Product::getProd(TokenType token) {
  using TokenDefinitions::Grammar;
  auto prod = std::find_if(Grammar.begin(), Grammar.end(),
      [token](Product prod) -> bool { return prod.getType() == token; });
  if (prod == Grammar.end()) return nullptr;
  return &*prod;
}


