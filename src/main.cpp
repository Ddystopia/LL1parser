#include <iostream>
#include <memory>
#include <string>
#include "../headers/Evaluator.h"
#include "../headers/Parser.h"

std::string join(char *cstr[], int len) {
  std::string result;

  for(int i(0); i < len; ++i) {
    result.append(std::string(cstr[i]));
  }

  return result;
}

int main(int argc, char *argv[]) {
  Evaluator evaluator;
  Parser parser; 
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
