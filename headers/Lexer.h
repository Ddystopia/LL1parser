#ifndef LEXER
#define LEXER

#include <vector>
#include <string>
#include "Token.h"

class Lexer {
  private:
    int m_offset;
    std::string m_source;
    const char m_spaces[4]{' ', '\n', '\t', '\r'};

  public:
    Lexer();
    std::vector<Token*> *tokenize(std::string source);

    bool inBounds();
    void skipSpaces();
    void cleanUp();
    Token* staticToken();
    Token* dynamicToken();
  
};

#endif
