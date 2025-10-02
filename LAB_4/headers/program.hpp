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

  bool handleHumanCase() const;
  bool handleDogCase() const;
  bool handleCatCase() const;

  int getValidChoice(int min, int max) const;

public:
  bool run(int choice) const;
};