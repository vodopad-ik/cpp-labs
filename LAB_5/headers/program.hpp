#pragma once
#include "array.impl.hpp"
#include "menu.hpp"
#include <functional>
#include <string>
using std::function;
using std ::string;

class Program {
private:
  int getValidChoice(int min, int max) const;
  template <class T> Array<T> createArr(int &choice);
  template <class T> bool useTypeArr(function<T(const string &)> inputFunc);

public:
  bool run(int choice);
};