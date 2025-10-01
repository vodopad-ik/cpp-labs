#pragma once
#include "mammal.hpp"
#include <string>
using namespace std;

class Human : public Mammal {
private:
  string status;

public:
  Human(const string &name, int age, const string &status);
  string getStatus() const;
  void setStatus(const string &value);
  void describe() const override;
};