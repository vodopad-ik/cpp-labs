#pragma once
#include "classA.hpp"
#include "classB.hpp"
#include <complex>

class C : public B {
private:
  double c;
  double x1 = 0;
  double x2 = 0;

public:
  explicit C(double a_val = 1.0, double b_val = 0.0, double c_val = 0.0);
  void setC(double val);
  double getC() const;
  void printEquation() const;
  void printComplex(const std::complex<double> &z) const;
  void solve() const;
};