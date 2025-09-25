#pragma once

class A {
protected:
  double a;

public:
  A(double a_val = 1.0);
  void setA(double val);
  double getA() const;
};