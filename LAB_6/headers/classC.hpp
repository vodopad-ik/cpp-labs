#pragma once
#include "classA.hpp"
#include "classB.hpp"
#include "parser.hpp"
#include <complex>
#include <string_view>

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
  std::complex<double> getX1() const;
  std::complex<double> getX2() const;
  void printEquation() const;
  void printComplex(const std::complex<double> &z) const;
  double searchDiscrimen() const;
  void solve();
  void printSolve() const;
};