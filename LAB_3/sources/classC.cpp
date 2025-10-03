#include "classC.hpp"
#include "classA.hpp"
#include "classB.hpp"
#include <complex>
#include <iostream>
using namespace std;

C::C(double a_val, double b_val, double c_val) : B(a_val, b_val), c(c_val) {}
void C::setC(double val) { c = val; }
double C::getC() const { return c; }
void C::printEquation() const {
  double a = getA();
  double b = getB();
  cout << a << "x^2" << (b > 0 ? " + " : " - ") << abs(b) << 'x'
       << (c > 0 ? " + " : " - ") << abs(c) << " = 0" << endl;
}

void C::printComplex(const complex<double> &z) const {
  double re = z.real();
  double im = z.imag();

  cout << re;
  if (im > 0) {
    cout << " + " << im << "i";
  } else if (im < 0) {
    cout << " - " << -im << "i";
  }
  cout << endl;
}

double C::searchDiscrimen() const {
  double a = getA();
  double b = getB();
  return b * b - 4 * a * c;
}
void C::solve() {
  double a = getA();
  double b = getB();
  double D = searchDiscrimen();
  if (a == 0)
    return;

  if (D > 0) {
    x1 = complex<double>((-b + sqrt(D)) / (2 * a), 0);
    x2 = complex<double>((-b - sqrt(D)) / (2 * a), 0);
  } else if (D == 0) {
    x1 = x2 = complex<double>((-b / (2 * a)), 0);
  } else {
    complex<double> sqrtD = sqrt(complex<double>(D, 0));
    x1 = (-b + sqrtD) / (2.0 * a);
    x2 = (-b - sqrtD) / (2.0 * a);
  }
  is_solve = true;
}

void C::printSolve() const {
  cout << "\nРешение уравнения: ";
  printEquation();
  if (getA() == 0) {
    cout << "Это не квадратное уравнение (a=0).\n";
    return;
  }
  if (is_solve == false)
    return;
  double D = searchDiscrimen();
  cout << "Дискриминант D = " << D << endl;
  if (D > 0) {
    cout << "Два действительных корня:\n";
    cout << "x1 = ";
    printComplex(x1);
    cout << "x2 = ";
    printComplex(x2);
  } else if (D == 0) {
    cout << "Один действительный корень:\n";
    cout << "x = ";
    printComplex(x1);
  } else {
    cout << "Два комплексных корня:\n";
    cout << "x1 = ";
    printComplex(x1);
    cout << "x2 = ";
    printComplex(x2);
  }
}