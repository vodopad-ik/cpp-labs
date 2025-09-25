#include "classC.hpp"
#include "classA.hpp"
#include "classB.hpp"
#include <complex>
#include <iostream>
using namespace std;

C::C(double a_val, double b_val, double c_val)
    : B(a_val, b_val), c(c_val), x1(0), x2(0) {}
void C::setC(double val) { c = val; }
double C::getC() const { return c; }
void C::printEquation() const {
  cout << a << "x^2" << (b > 0 ? " + " : " - ") << abs(b) << 'x'
       << (c > 0 ? " + " : " - ") << abs(c) << " = 0" << endl;
}

void C::printComplex(const complex<double> &z) {
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

void C::solve() {
  double D = b * b - 4 * a * c;
  cout << "\nРешение уравнения: ";
  printEquation();
  cout << "Дискриминант D = " << D << endl;
  if (a == 0) {
    cout << "Это не квадратное уравнение (a=0).\n";
    return;
  }

  if (D > 0) {
    double x1 = (-b + sqrt(D)) / (2 * a);
    double x2 = (-b - sqrt(D)) / (2 * a);
    cout << "Два действительных корня:\n";
    cout << "x1 = " << x1 << "\n";
    cout << "x2 = " << x2 << "\n";
  } else if (D == 0) {
    double x = -b / (2 * a);
    cout << "Один действительный корень: x = " << x << "\n";
  } else {
    complex<double> sqrtD = sqrt(complex<double>(D, 0));
    complex<double> x1 = (-b + sqrtD) / (2.0 * a);
    complex<double> x2 = (-b - sqrtD) / (2.0 * a);
    cout << "Два комплексных корня:\n";
    cout << "x1 = ";
    printComplex(x1);
    cout << "x2 = ";
    printComplex(x2);
  }
}