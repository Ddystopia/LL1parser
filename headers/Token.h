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
    const std::string &getStrType() const { return m_type; }; // for debug, dont use it for productoin

    friend bool operator==(const TokenType &left, const TokenType &right);
    friend bool operator!=(const TokenType &left, const TokenType &right);
    friend bool operator<(const TokenType &left, const TokenType &right);
};

bool operator==(const TokenType &left, const TokenType &right);
bool operator!=(const TokenType &left, const TokenType &right);
bool operator<(const TokenType &left, const TokenType &right);

class Token {
  private:
    std::string m_value;
    TokenType m_type;
    int m_offset;
  public:
    Token(TokenType type, std::string value, int m_offset);
    const std::string &getValue() const { return m_value; };
    const TokenType &getType() const { return m_type; };
    const int &getOffset() const { return m_offset; };
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
// for lexer
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
#endif
