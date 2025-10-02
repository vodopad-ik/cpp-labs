#pragma once
#include "cat.hpp"
#include "dog.hpp"
#include "human.hpp"
#include "menu.hpp"
class Program {
private:
  Human useObjectHuman() const;
  Dog useObjectDog() const;
  Cat useObjectCat() const;

public:
  bool run(int choice) const;
};