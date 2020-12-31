#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "../headers/Lexer.h"
#include "../headers/Token.h"
#include "../headers/Node.h"

class Parser {
  private:
    int m_tokenId { -1 };
    std::string m_error {""};
    std::vector<Token*> *m_tokens { nullptr };
    std::map<
      std::pair<int, TokenType>, 
      std::pair<std::shared_ptr<Node>, int>
    > m_cache;
    
    std::shared_ptr<Node> calc (TokenType token, int expectedEndId = -1);
    const std::string &getError() const { return m_error; };
    const Token* peek();
    const Token* get();
    void setId(int id) { m_tokenId = id; };
    void setError(std::string &&err) { m_error = err; };
    void clear();

    void memorize(std::pair<int, TokenType> lockation,
      std::pair<std::shared_ptr<Node>, int> data);
 public:
    Parser();
    ~Parser();
    std::shared_ptr<Node> parse(const std::string &source);
};

#endif
