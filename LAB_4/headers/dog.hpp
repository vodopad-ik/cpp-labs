#pragma once
#include "animal.hpp"
#include <string>
using namespace std;

class Dog : public Animal {
private:
  const string breed;

public:
  Dog(const string &name, int age, double weight, const string& breed);
  string getBreed() const;
  void voice()const;
  void describe() const override;
};