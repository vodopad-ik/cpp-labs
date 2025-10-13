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

  void validateEquationString(const std::string &str);
  void parseEquationString(const std::string &eq);

  void parseA(std::string &simplified, double &a);
  void parseB(std::string &simplified, double &b);
  void parseC(const std::string &simplified, double &c_val);
  double parseNumber(const std::string &num_str, double default_value = 1.0);
  bool isAFound(const std::string &simplified);

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