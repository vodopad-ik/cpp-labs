#include "human.hpp"
#include "utils.hpp"
#include "consts.hpp"
#include <iostream> 
using std::cout;

Human::Human(const string &name, int age, const string &status)
    : Mammal(name, age), status(status) {}
string Human::getStatus() const { return status; }
void Human::setStatus(std::string_view value) { status = value; }
void Human::describe() const {
  clearScreen();
  cout << SOLID_LINE;
  cout << " INFO: " << getName() << '\n';
  cout << BROKEN_LINE;
  cout << " Привет! Меня зовут " << getName()<< ".\n";
  cout << " Мой возраст составляет " << getAgeStr()<< '\n';
  cout << " Я - " << status<< ".\n";
  cout << SOLID_LINE;
}
