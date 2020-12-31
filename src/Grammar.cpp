#include "../headers/Token.h"
#include <vector>
#include <string>

// Non-terminals
const TokenType EXPR = TokenType("EXPR");
const TokenType SUM = TokenType("SUM");
const TokenType DER = TokenType("DER");
const TokenType MUL = TokenType("MUL");
const TokenType DIV = TokenType("DIV");
const TokenType POW = TokenType("POW");
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

// std::vector<Product> TokenDefinitions::Grammar {
//   Product(EXPR, {
//     { TERM },
//     { TERM, PLUS, EXPR },
//     { TERM, MINUS, EXPR },
//   }),
//   Product(TERM, {
//     { POW },
//     { POW, STAR, TERM },
//     { POW, DIV, TERM },
//   }), 
//   Product(POW, {
//     { FACT }, { FACT, POWER, POW },
//   }),
//   Product(FACT, {
//     { NUM }, { LP, EXPR, RP },
//   }),
// };

std::vector<Product> TokenDefinitions::Grammar {
  Product(EXPR, {
    { SUM }, { DER },
  }), 
  Product(SUM, {
    { MUL }, { DIV }, { MUL, PLUS, EXPR }, { DIV, PLUS, EXPR }
  }), 
  Product(DER, {
    { MUL }, { DIV }, { MUL, MINUS, EXPR }, { DIV, MINUS, EXPR }
  }), 
  Product(MUL, {
    { POW }, { POW, STAR, MUL }, { POW, STAR, DIV }
  }),
  Product(DIV, {
    { POW }, { POW, SLASH, DER }, { POW, SLASH, MUL }
  }),
  Product(POW, {
    { FACT }, { FACT, POWER, POW },
  }),
  Product(FACT, {
    { NUM }, { LP, EXPR, RP },
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

