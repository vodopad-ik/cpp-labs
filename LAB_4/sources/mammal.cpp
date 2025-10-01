#include "mammal.hpp"

Mammal::Mammal(const string &name, int age) : name(name), age(age) {}
string Mammal::getName() const { return name; }
int Mammal::getAge() const { return age; }
void Mammal::setAge(int value) { age = value; }