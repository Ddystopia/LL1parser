#ifndef LEXER
#define LEXER

#include <vector>
#include <string>
#include <string_view>
#include "Token.h"

class Lexer {
  private:
    int m_offset {0};
    std::string_view m_source {};
    const std::vector<char> m_spaces {' ', '\n', '\t', '\r'};

  public:
    Lexer();
    std::vector<Token*> *tokenize(const std::string &source);

    bool inBounds();
    void skipSpaces();
    void cleanUp();
    Token* staticToken();
    Token* dynamicToken();
};

#endif
