#pragma once
#include "mammal.hpp"
#include <string>
#include <string_view>

class Human : public Mammal {
private:
  string status;

public:
  Human(const string &name, int age, const string &status); 
  string getStatus() const;
  void setStatus(std::string_view value);
  void describe() const override;
};