#pragma once
#include "classA.hpp"
#include "classB.hpp"
#include <complex>

class C : public B {
protected:
  double c;
  double x1, x2;

public:
  C(double a_val = 1.0, double b_val = 0.0, double c_val = 0.0);
  void setC(double val);
  double getC() const;
  void printEquation() const;
  void printComplex(const std::complex<double> &z);
  void solve();
};