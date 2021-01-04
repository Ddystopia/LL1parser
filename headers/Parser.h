#ifndef PARSER
#define PARSER

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "../headers/Lexer.h"
#include "../headers/Token.h"
#include "../headers/Node.h"

struct LockationData {
  std::shared_ptr<Node> node;
  std::string error;
  int tokenId;
};

class Parser {
  private:
    int m_tokenId { -1 };
    std::string m_error {""};
    std::vector<Token*> *m_tokens { nullptr };
    std::map<
      std::pair<int, TokenType>, 
      LockationData
    > m_cache;
    
    std::shared_ptr<Node> calc (TokenType token);
    const Token* now();
    const Token* peek();
    const Token* get();
    const std::string &getError() const { return m_error; };
    const std::vector<TokenType> *getEq(std::vector<std::vector<TokenType>> &eqs);
    bool isCorrect(std::vector<TokenType> eqS);
    bool hasError() const { return m_error.size() != 0; };
    void setId(int id) { m_tokenId = id; };
    void memorize(std::pair<int, TokenType> lockation, LockationData data);
    void setError(std::string &&err) { m_error = err; };
    void clear();
 public:
    Parser();
    ~Parser();
    std::shared_ptr<Node> parse(const std::string &source);
};

#endif
