#pragma once
#include "mammal.hpp"

class Animal : public Mammal {
private:
  double weight;

public:
  Animal(const string& name, int age, double weight);
  double getWeight() const;
  void setWeight(double value);
  void voice()const;
};