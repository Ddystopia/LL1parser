#include "../headers/Token.h"
#include <vector>
#include <string>

// Non-terminals
const TokenType EXPR = TokenType("EXPR");
const TokenType EXPR2 = TokenType("EXPR'");
const TokenType TERM = TokenType("TERM");
const TokenType TERM2 = TokenType("TERM'");
const TokenType POW = TokenType("POW");
const TokenType POW2 = TokenType("POW'");
const TokenType FACT = TokenType("FACT");
// Terminals
const TokenType PLUS = TokenType("PLUS");
const TokenType MINUS = TokenType("MINUS");
const TokenType STAR = TokenType("STAR");
const TokenType SLASH = TokenType("SLASH");
const TokenType LP = TokenType("LP");
const TokenType RP = TokenType("RP");
const TokenType POWER = TokenType("POWER");
const TokenType NUM = TokenType("NUM");
const TokenType WORD = TokenType("WORD");

std::vector<Product> TokenDefinitions::Grammar {
  Product(EXPR, {
    { TERM, EXPR2 }
  }),
  Product(EXPR2, {
    { PLUS, TERM, EXPR2 }, { MINUS, TERM, EXPR2 }, {}
  }),
  Product(TERM, {
    { POW, TERM2 }
  }), 
  Product(TERM2, {
    { STAR, POW, TERM2 }, { SLASH, POW, TERM2 }, {}
  }), 
  Product(POW, {
    { FACT, POW2 }, 
  }),
  Product(POW2, {
    { POWER, FACT, POW2}, {}
  }),
  Product(FACT, {
    { NUM }, { LP, EXPR, RP }, { MINUS, FACT }, { PLUS, FACT },
  }),
};

std::vector<StaticTokenDefinition> TokenDefinitions::statics {
  StaticTokenDefinition("+", PLUS),
  StaticTokenDefinition("-", MINUS),
  StaticTokenDefinition("*", STAR),
  StaticTokenDefinition("/", SLASH),
  StaticTokenDefinition("(", LP),
  StaticTokenDefinition(")", RP),
  StaticTokenDefinition("^", POWER),
};

std::vector<DynamicTokenDefinition> TokenDefinitions::dynamics {
  DynamicTokenDefinition("[0-9]+(\\.[0-9]+)?", NUM),
  //DynamicTokenDefinition("[a-zA-Z_][a-zA-Z_-?]*", WORD),
};

