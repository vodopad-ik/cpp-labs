#pragma once
#include <string>
using std::string;

class Mammal {
private:
  string name;
  int age;

public:
  Mammal(const string &name, int age);
  virtual ~Mammal() = default; 
  string getName() const;
  int getAge() const;
  void setAge(int value);
  string getAgeStr()const ;
  virtual void describe() const = 0;
};