#pragma once
#include "animal.hpp"
#include <string>

class Cat : public Animal {
private:
  const string color;

public:
  Cat(const string &name, int age, double weight, const string &color);
  string getColor() const;
  void voice() const;
  void describe() const override; 
};