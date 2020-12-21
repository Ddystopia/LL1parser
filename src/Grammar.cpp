#include "../headers/Token.h"
#include "../headers/Node.h"
#include <vector>
#include <string>

// Non-terminals
const TokenType EXPR = TokenType("EXPR");
const TokenType TERM = TokenType("TERM");
const TokenType POW = TokenType("POW");
const TokenType FACT = TokenType("FACT");
// Terminals
const TokenType PLUS = TokenType("PLUS");
const TokenType MINUS = TokenType("MINUS");
const TokenType STAR = TokenType("STAR");
const TokenType DIV = TokenType("DIV");
const TokenType LP = TokenType("LP");
const TokenType RP = TokenType("RP");
const TokenType POWER = TokenType("POWER");
const TokenType NUM = TokenType("NUM");

class Expr: public Node {
  public:
    Expr(std::vector<const Token *>&args) : Node(args) {};
    virtual long double evaluate() const {
      if (m_arguments.size() == 1) m_arguments[0].evaluate();
    }
    virtual Node * getNewNode(std::vector<const Token *>& args) const {
      return new Expr(args);
    }
};

std::vector<Product> TokenDefinitions::Grammar {
  Product(EXPR, {
    { TERM },
    { TERM, PLUS, EXPR },
    { TERM, MINUS, EXPR },
  }),
  Product(TERM, {
    { POW },
    { POW, STAR, TERM },
    { POW, DIV, TERM },
  }),
  Product(POW, {
    { FACT },
    { FACT, POWER, POW },
  }),
  Product(FACT, {
    { NUM },
    { LP, EXPR, RP },
  }),
};

std::vector<StaticTokenDefinition> TokenDefinitions::statics {
  StaticTokenDefinition("+", PLUS),
  StaticTokenDefinition("-", MINUS),
  StaticTokenDefinition("*", STAR),
  StaticTokenDefinition("/", DIV),
  StaticTokenDefinition("(", LP),
  StaticTokenDefinition(")", RP),
  StaticTokenDefinition("^", POWER),
};

std::vector<DynamicTokenDefinition> TokenDefinitions::dynamics {
  DynamicTokenDefinition("[0-9]+", NUM),
};
