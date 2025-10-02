#include "mammal.hpp"
#include <iostream>
#include <format>

Mammal::Mammal(const string &name, int age) : name(name), age(age) {}
string Mammal::getName() const { return name; }
int Mammal::getAge() const { return age; }
void Mammal::setAge(int value) { age = value; }
string Mammal::getAgeStr() const {
  string ending;
    if (age % 10 == 1 && age % 100 != 11) ending= " год.";
    else if (age % 10 >= 2 && age % 10 <= 4 && (age % 100 < 10 || age % 100 >= 20)) {
        ending= " года.";
    }
    else ending= " лет.";
    return std::format("{}{}", age, ending);
}