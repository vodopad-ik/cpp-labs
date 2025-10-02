#pragma once
#include "cat.hpp"
#include "dog.hpp"
#include "human.hpp"

class Program {
private:
  Human useObjectHuman() const;
  Dog useObjectDog() const;
  Cat useObjectCat() const;

public:
  bool run(int choice) const;
};