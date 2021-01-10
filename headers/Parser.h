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
    std::vector<Product> Grammar;
    Lexer lexer;

    int m_tokenId { -1 }; // start before array
    std::string m_error {""};
    std::vector<Token*> *m_tokens { nullptr };
    std::map<
      std::pair<int, TokenType>, 
      LockationData
    > m_cache;
    
    std::shared_ptr<Node> calc (TokenType token);
    const Token* now() const; // get node is parsed now
    const Token* peek() const; // get lookahead
    const Token* get(); // get lookahead and shift by one
    const std::string &getError() const { return m_error; };
    const std::vector<TokenType> *getEq(std::vector<std::vector<TokenType>> &eqs);
    const Product *getProd(TokenType token) const;

    bool isCorrect(std::vector<TokenType> &eqS); 
    bool isNonterminal(TokenType token) const;
    bool hasEpsilon(TokenType token) const;
    bool hasError() const { return m_error.size() != 0; };

    void setId(int id) { m_tokenId = id; };
    void memorize(std::pair<int, TokenType> lockation, LockationData data);
    void setError(std::string &&err) { m_error = err; };
    void clear();
 public:
    Parser(
      std::vector<Product> &&Grammar,
      std::vector<StaticTokenDefinition> &&statics,
      std::vector<DynamicTokenDefinition> &&dynamics
    );
    ~Parser();
    std::shared_ptr<Node> parse(std::string &source);
};

#endif
