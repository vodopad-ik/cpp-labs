#pragma once
#include "cat.hpp"
#include "dog.hpp"
#include "human.hpp"

class Program{
  private:
  Human useObjectHuman();
  Dog useObjectDog();
  Cat useObjectCat();
  public:
  bool run(int choice);
};