#include <iostream>
#include <memory>
#include <string>
#include "../headers/Evaluator.h"
#include "../headers/Parser.h"

std::string join(char *cstr[], int len);

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

Parser parser { 
  {
    { EXPR, {
      { TERM, EXPR2 }
    } },
    { EXPR2, {
      { PLUS, TERM, EXPR2 }, { MINUS, TERM, EXPR2 }, {}
    } },
    { TERM, {
      { POW, TERM2 }
    } }, 
    { TERM2, {
      { STAR, POW, TERM2 }, { SLASH, POW, TERM2 }, {}
    } }, 
    { POW, {
      { FACT, POW2 }, 
    } },
    { POW2, {
      { POWER, FACT, POW2}, {}
    } },
    { FACT, {
      { NUM }, { LP, EXPR, RP }, 
      { MINUS, FACT }, { PLUS, FACT },
      { WORD, LP, EXPR, RP }
    } },
  },
  {
    { "+", PLUS },
    { "-", MINUS },
    { "*", STAR },
    { "/", SLASH },
    { "(", LP },
    { ")", RP },
    { "^", POWER },
  },
  {
    { "[0-9]+(\\.[0-9]+)?", NUM },
    { "[a-zA-Z_]+", WORD },
  } 
};

Evaluator evaluator;

int main(int argc, char *argv[]) {
  std::string expression{ join(argv + 1, argc - 1) };

  long double result;
  try {
    result = evaluator.eval(parser.parse(expression));
  } catch (std::string &err) {
    std::cout << "Error: " << err << std::endl;
    return 1;
  }

  std::cout << "Result: " << result << "\n";

  return 0;
}

std::string join(char *cstr[], int len) {
  std::string result;

  for(int i(0); i < len; ++i) {
    result.append(std::string(cstr[i]));
  }

  return result;
}


