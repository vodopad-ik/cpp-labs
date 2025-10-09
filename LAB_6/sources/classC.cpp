#include "classC.hpp"
#include "classA.hpp"
#include "classB.hpp"
#include <algorithm>
#include <cctype>
#include <complex>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <stdexcept>
using namespace std;

C::C(double a_val, double b_val, double c_val) : B(a_val, b_val), c(c_val) {}
C::C(const std::string &equation) {
  parseEquationFromString(equation);
}
C::C() {
  std::string equation_str =
      inputEquationString("Введите квадратное уравнение: ");
  parseEquationFromString(equation_str);
}

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

void C::validateEquationString(const std::string &equationStr) {
  regex allowed_pattern(R"(^[0-9a-zA-Z\s\.\+\-\*\/\^=x]+$)");

  if (!regex_match(equationStr, allowed_pattern)) {
    throw invalid_argument("Внимание! Строка содержит недопустимые символы. "
                           "Разрешены только цифры, 'x', "
                           "математические операторы(+, -, ^, =) и пробелы.");
  }

  if (equationStr.find('x') == string::npos)
    throw invalid_argument(
        "Внимание!: Уравнение должно содержать переменную 'x'");

  if (equationStr.find('=') == string::npos)
    throw invalid_argument("Внимание! Уравнение должно содержать знак '='");

  if (equationStr.find("x^2") == string::npos &&
      equationStr.find("x*x") == string::npos &&
      equationStr.find("x**2") == string::npos) {
    throw invalid_argument(
        "Внимание! Уравнение должно быть квадратным (содержать x^2 или x*x)");
  }
}

void C::parseEquationFromString(const std::string &equationStr) {
  validateEquationString(equationStr);

  regex equation_pattern(
      R"(([-+]?\d*\.?\d*)\s*\*?\s*x\^2\s*([-+]?\d*\.?\d*)\s*\*?\s*x\s*([-+]?\d*\.?\d*)\s*=\s*0)");
  smatch matches;

  if (regex_search(equationStr, matches, equation_pattern) &&
      matches.size() == 4) {
    double a_val = 1.0, b_val = 0.0, c_val = 0.0;

    if (!matches[1].str().empty() && matches[1].str() != "+" &&
        matches[1].str() != "-") {
      a_val = stod(matches[1].str());
    } else if (matches[1].str() == "-") {
      a_val = -1.0;
    }

    if (!matches[2].str().empty() && matches[2].str() != "+" &&
        matches[2].str() != "-") {
      b_val = stod(matches[2].str());
    } else if (matches[2].str() == "-") {
      b_val = -1.0;
    }

    if (!matches[3].str().empty() && matches[3].str() != "+" &&
        matches[3].str() != "-") {
      c_val = stod(matches[3].str());
    } else if (matches[3].str() == "-") {
      c_val = -1.0;
    }
    setA(a_val);
    setB(b_val);
    setC(c_val);
  } else {
    throw invalid_argument("Внимание! Не удалось распознать уравнение. "
                           "Ожидается формат: ax^2 + bx + c = 0");
  }
}