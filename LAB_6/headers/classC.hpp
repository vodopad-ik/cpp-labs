#pragma once
#include "classA.hpp"
#include "classB.hpp"
#include <complex>
#include <string>
using std::string;

class C : public B {
private:
  double c;
  std::complex<double> x1;
  std::complex<double> x2;
  bool is_solve = false;
  string additional_info;

public:
  explicit C(double a_val = 1.0, double b_val = 0.0, double c_val = 0.0);
  void setC(double val);
  double getC() const;
  void printEquation() const;
  void printComplex(const std::complex<double> &z) const;
  double searchDiscrimen() const;
  void solve();
  void printSolve() const;
};