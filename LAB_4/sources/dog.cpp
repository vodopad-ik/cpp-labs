#include "dog.hpp"
#include "utils.hpp"
#include "consts.hpp"
#include <iostream>
#include <format>
using std::cout;


Dog::Dog(const string &name, int age, double weight, const string &breed)
    : Animal(name, age, weight), breed(breed) {}
string Dog::getBreed() const { return breed; }
void Dog::voice() const { cout << "Гав-гав!\n"; }
void Dog::describe() const {
  Utils::clearScreen();
  cout << SOLID_LINE;
  cout << " INFO: " << getName()<< '\n';
  cout << BROKEN_LINE;
  cout << " Возраст составляет " << getAgeStr() << "\n";
  cout << " Порода: " << breed<< ".\n";
  cout << " Вес составляет " << getWeight()<< " кг.\n";
  cout << SOLID_LINE;
}