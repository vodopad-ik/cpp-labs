#include "classC.hpp"
#include "classA.hpp"
#include "classB.hpp"
#include <algorithm>
#include <cctype>
#include <regex>
#include <stdexcept>
using namespace std;

C::C(double a_val, double b_val, double c_val) : B(a_val, b_val), c(c_val) {
  if (a_val == 0)
    throw invalid_argument(
        "Коэффициент a не может быть равен нулю для квадратного уравнения");
}
C::C(const std::string &equation) { parseEquationString(equation); }
C::C() {
  std::string equation_str =
      Utils::inputString("Введите квадратное уравнение: ");
  parseEquationString(equation_str);
}

void C::setC(double val) { c = val; }
double C::getC() const { return c; }
std::complex<double> C::getX1() const { return x1; }
std::complex<double> C::getX2() const { return x2; }
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

void C::validateEquationString(const std::string &str) {
  const string allowed_сhars = "0123456789+-*=^xX. "
  for (char c : str) {
    if (allowed_сhars.find(c) == string::npos) {
      throw invalid_argument("Обнаружены запрещенные символы. Разрешены только "
                             "цифры, латинские буквы, математические символы и "
                             "точка для вещественных чисел: + - * = ^ x ( ) .");
    }
  }

  // Проверка на корректное использование точки (для вещественных чисел)
  bool hasDigit = false;
  for (size_t i = 0; i < str.length(); i++) {
    char c = str[i];

    if (isdigit(c)) {
      hasDigit = true;
    }

    // Проверяем, что точка используется правильно (между цифрами или после
    // цифры)
    if (c == '.') {
      // Точка не может быть в начале или конце числа
      if (i == 0 || i == str.length() - 1) {
        throw invalid_argument("Некорректное использование точки в числе");
      }
      // Перед точкой должна быть цифра
      if (!isdigit(str[i - 1])) {
        throw invalid_argument("Перед точкой должна быть цифра");
      }
      // После точки должна быть цифра
      if (i + 1 < str.length() && !isdigit(str[i + 1])) {
        throw invalid_argument("После точки должна быть цифра");
      }
    }
  }

  if (!hasDigit) {
    throw invalid_argument("Строка должна содержать хотя бы одну цифру");
  }
}

void C::parseEquationString(const string &equationStr) {
  validateEquationString(equationStr);
  string simplified = equationStr;

  // Предварительная обработка строки
  simplified.erase(remove(simplified.begin(), simplified.end(), ' '),
                   simplified.end());
  transform(simplified.begin(), simplified.end(), simplified.begin(),
            ::tolower);

  cout << "Упрощенная строка: " << simplified << endl;

  double a = 1.0, b = 0.0, c_val = 0.0;

  // Парсим коэффициенты по очереди
  parseA(simplified, a);
  parseB(simplified, b);
  parseC(simplified, c_val);

  // Проверяем, что уравнение квадратное (есть x^2)
  if (!isAFound(simplified)) {
    throw invalid_argument("Не удалось распознать квадратное уравнение. "
                           "Убедитесь, что есть член с x^2");
  }

  // Устанавливаем коэффициенты
  setA(a);
  setB(b);
  setC(c_val);

  cout << "Распознанные коэффициенты: a=" << a << ", b=" << b << ", c=" << c_val
       << endl;
}

// Вспомогательные приватные методы для парсинга
void C::parseA(string &simplified, double &a) {
  regex a_pattern(R"(([+-]?\d+\.?\d*)x\^2)");
  smatch a_match;

  if (regex_search(simplified, a_match, a_pattern) && a_match.size() > 1) {
    string a_str = a_match[1].str();
    cout << "Найден коэффициент a: '" << a_str << "'" << endl;

    a = parseNumber(a_str, 1.0);
    simplified = regex_replace(simplified, a_pattern, "");
    cout << "Строка после удаления a: " << simplified << endl;
  }
}

void C::parseB(string &simplified, double &b) {
  regex b_pattern(R"(([+-]?\d+\.?\d*)x(?!\^))");
  smatch b_match;

  if (regex_search(simplified, b_match, b_pattern) && b_match.size() > 1) {
    string b_str = b_match[1].str();
    cout << "Найден коэффициент b: '" << b_str << "'" << endl;

    b = parseNumber(b_str, 1.0);
    simplified = regex_replace(simplified, b_pattern, "");
    cout << "Строка после удаления b: " << simplified << endl;
  }
}

void C::parseC(const string &simplified, double &c_val) {
  size_t equal_pos = simplified.find('=');
  if (equal_pos == string::npos)
    return;

  string before_equal = simplified.substr(0, equal_pos);
  cout << "Остаток перед '=': '" << before_equal << "'" << endl;

  if (!before_equal.empty() && before_equal != "+" && before_equal != "-") {
    try {
      c_val = Utils::stringToDouble(before_equal);
      cout << "Найден коэффициент c: " << c_val << endl;
    } catch (const exception &e) {
      cout << "Не удалось распознать c: " << before_equal << " (" << e.what()
           << ")" << endl;
    }
  }
}

double C::parseNumber(const string &num_str, double default_value) {
  if (num_str.empty() || num_str == "+")
    return default_value;
  if (num_str == "-")
    return -default_value;

  try {
    return Utils::stringToDouble(num_str);
  } catch (const exception &e) {
    throw invalid_argument("Некорректный числовой формат: '" + num_str + "'");
  }
}

bool C::isAFound(const string &simplified) {
  // Проверяем наличие x^2 в упрощенной строке
  return simplified.find("x^2") != string::npos ||
         regex_search(simplified, regex(R"(([+-]?\d+\.?\d*)x\^2)"));
}