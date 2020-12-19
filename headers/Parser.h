#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include "../headers/Lexer.h"
#include "../headers/Token.h"

typedef long double ld;

class Parser{
  private:
    int m_tokenId;
    std::vector<Token*> *m_tokens;
    
    ld calc ();
    Token* peek();
    Token* get();
    void setId(int id);
    void clear();

    ld expr();
    ld term();
    ld pow();
    ld fact();
  public:
    Parser();
    ld parse(std::string source);
};

#endif
