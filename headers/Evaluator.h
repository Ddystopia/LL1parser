#ifndef EVALUATOR
#define EVALUATOR

#include "../headers/Node.h"
#include <memory>
#include <string>

class Evaluator {
  public:
    long double eval(std::shared_ptr<Node> node);
};

#endif
