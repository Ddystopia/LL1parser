#include <iostream>
#include <memory>
#include <string>
#include "../headers/Parser.h"

std::string join(char *cstr[], int len) {
  std::string result;

  for(int i(0); i < len; ++i) {
    result.append(std::string(cstr[i]));
  }

  return result;
}

int main(int argc, char *argv[]) {
  Parser parser; 
  std::string expression{ join(argv + 1, argc - 1) };

  std::shared_ptr<Node> result;
  result = parser.parse(expression);

  return 0;
}
