#pragma once
#include "classA.hpp"
#include "classB.hpp"
#include <complex>

class C : public B {
private:
  double c;
  std::complex<double> x1;
  std::complex<double> x2;
  bool is_solve = false;

public:
  explicit C(double a_val, double b_val, double c_val);
  explicit C(const std::string &equation);
  explicit C();
  void setC(double val);
  double getC() const;
  void printEquation() const;
  void printComplex(const std::complex<double> &z) const;
  double searchDiscrimen() const;
  void solve();
  void printSolve() const;

  void parseEquationFromString(const std::string &equationStr);
  static void validateEquationString(const std::string &equationStr);
};