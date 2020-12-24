#ifndef TOKEN
#define TOKEN

#include <string>
#include <vector>
#include <regex>
#include <initializer_list>

class TokenType {
  private:
    std::string m_type;
  public:
    TokenType(std::string type);
    bool isProduct() const;
    const std::string &getType() const { return m_type; };
    friend bool operator==(const TokenType &left, const TokenType &right);
    friend bool operator!=(const TokenType &left, const TokenType &right);
};

bool operator==(const TokenType &left, const TokenType &right);
bool operator!=(const TokenType &left, const TokenType &right);

class Token {
  private:
    std::string m_value;
    TokenType m_type;
  public:
    Token(TokenType type, std::string value);
    const std::string &getValue() const { return m_value; };
    const TokenType &getType() const { return m_type; };
};

template <class T>
class TokenDefinition {
  private:
    TokenType m_type;
    T m_represantation;
  public:
    TokenDefinition(T repres, TokenType type);
    const TokenType &getType() const { return m_type; };
    const T &getRepres() const { return m_represantation; };
};

class StaticTokenDefinition : public TokenDefinition<std::string> {
  public:
    StaticTokenDefinition(std::string repres, TokenType type);
};

class DynamicTokenDefinition : public TokenDefinition<std::regex> {
  public:
    DynamicTokenDefinition(std::string repres, TokenType type);
};

class Product {
  typedef std::vector< std::vector<TokenType> > eqv;

  private:
    TokenType m_type;
    eqv m_equalentSeries;

  public:
    Product(TokenType type, 
      std::initializer_list<std::initializer_list<TokenType>> equalentSeries);
    const TokenType &getType() const { return m_type; };
    const eqv &getEqualents() const { return m_equalentSeries; };
};

namespace TokenDefinitions {
  // Non-terminal
  extern std::vector<Product> Grammar;
  // Terminal
  extern std::vector<StaticTokenDefinition> statics;
  extern std::vector<DynamicTokenDefinition> dynamics;
}

#endif
