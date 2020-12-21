#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include "../headers/Lexer.h"
#include "../headers/Token.h"
#include "../headers/Node.h"

typedef long double ld;

class Parser{
  private:
    int m_tokenId;
    std::vector<Token*> *m_tokens;
    
    Node* calc (TokenType token);
    const Token* peek();
    const Token* get();
    void setId(int id);
    void clear();
    const Product *getProd(TokenType token);

 public:
    Parser();
    ~Parser();
    Node *parse(const std::string &source);
};

#endif
