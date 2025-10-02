#pragma once
#include <string>
using std::string;

class Mammal {
private:
  const string name;
  int age;

public:
  Mammal(const string &name, int age);
  virtual ~Mammal() = default; 
  string getName() const;
  int getAge() const;
  void setAge(int value);
  const string getAgeStr()const ;
  virtual void describe() const = 0;
};