#pragma once
#include "carManager.hpp"
#include "menu.hpp"

class Program {
private:
  int getValidChoice(int min, int max) const;

public:
  bool run(int choice) const;
};