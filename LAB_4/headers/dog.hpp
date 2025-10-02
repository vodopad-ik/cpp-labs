#pragma once
#include "animal.hpp"
#include <string>

class Dog : public Animal {
private:
  string breed;

public:
  Dog(const string &name, int age, double weight, const string& breed);
  string getBreed() const;
  void voice()const;
  void describe() const override;
};