#include "human.hpp"
#include "utils.hpp"
#include "consts.hpp"
#include <iostream>

Human::Human(const string &name, int age, const string &status)
    : Mammal(name, age), status(status) {}
string Human::getStatus() const { return status; }
void Human::setStatus(const string &value) { status = value; }
void Human::describe() const {
  clearScreen();
  int age = getAge();
  const string age_str =
      to_string(age) +
      ((age % 10 <= 4 && age % 10 >= 1 && age > 20) ? " год(а)." : " лет.");
  cout << SOLID_LINE;
  cout << " INFO: " << getName() << '\n';
  cout << BROKEN_LINE;
  cout << " Привет! Меня зовут " << getName()<< ".\n";
  cout << " Мой возраст составляет " << age_str<< '\n';
  cout << " Я - " << status<< ".\n";
  cout << SOLID_LINE;
}
