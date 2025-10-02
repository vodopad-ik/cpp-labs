#pragma once
#include "animal.hpp"
#include <string>

class Cat : public Animal {
private:
  string color;

public:
  Cat(const string &name, int age, double weight, const string &color);
  string getColor() const;
 void voice() const override;
  void describe() const override; 
};