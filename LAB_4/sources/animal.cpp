#include "animal.hpp"
#include <iostream>

Animal::Animal(const string &name, int age, double weight)
    : Mammal(name, age), weight(weight) {}
double Animal::getWeight() const { return weight; }
void Animal::setWeight(double value) { weight = value; }
void Animal::voice() const {std::cout << getName() << " издает звук животного!\n";}