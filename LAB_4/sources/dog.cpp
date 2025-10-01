#include "dog.hpp"
#include "utils.hpp"
#include "consts.hpp"
#include <iostream>

Dog::Dog(const string &name, int age, double weight, const string &breed)
    : Animal(name, age, weight), breed(breed) {}
string Dog::getBreed() const { return breed; }
void Dog::voice() const { cout << "Гав-гав!\n"; }
void Dog::describe() const {
  clearScreen();
  int age = getAge();
  const string age_str =
      to_string(age) +
      ((age % 10 <= 4 && age % 10 >= 1 && age > 20) ? " год(а)." : " лет.");
  cout << SOLID_LINE;
  cout << " INFO: " << getName()<< '\n';
  cout << BROKEN_LINE;
  cout << " Возраст составляет " << age_str << "\n";
  cout << " Порода: " << breed<< ".\n";
  cout << " Вес составляет " << getWeight()<< " кг.\n";
  cout << SOLID_LINE;
}