#pragma once
#include "classA.hpp"

class B : public A {
private:
  double b;

public:
  B(double a_val = 1.0, double b_val = 0.0);
  void setB(double val);
  double getB() const;
};