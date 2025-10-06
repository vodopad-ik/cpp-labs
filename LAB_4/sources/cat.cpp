#include "cat.hpp"
#include "utils.hpp"
#include "consts.hpp"
#include <iostream>
using std::cout;

Cat::Cat(const string &name, int age, double weight, const string &color)
    : Animal(name, age, weight), color(color) {}
string Cat::getColor() const { return color; }
void Cat::voice() const { cout << "Мяу-мяу!\n"; }
void Cat::describe() const {
  Utils::clearScreen();
  cout << SOLID_LINE;
  cout << " INFO: " << getName() << '\n';
  cout <<BROKEN_LINE;
  cout << " Возраст составляет " << getAgeStr() << "\n";
  cout << " Цвет шерсти: " << color << ".\n";
  cout << " Вес составляет " << getWeight() << " кг.\n";
  cout << SOLID_LINE;
}