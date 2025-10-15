#pragma once
#include "algorithms.hpp"
#include "menu.hpp"
#include "stack.hpp"

class Program {
private:
  int getValidChoice(int min, int max) const;
  Stack<int> inputStack()const ;
  void printStack(const Stack<int> &stack,
                  const std::string &message = "")const ;

public:
  void run();
};