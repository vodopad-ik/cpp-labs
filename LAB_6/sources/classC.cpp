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
  cout << a << "x^2" << (b < 0 ? " - " : " + ") << abs(b) << 'x'
       << (c < 0 ? " - " : " + ") << abs(c) << " = 0" << endl;
}

void C::printComplex(const complex<double> &z) const {
  double re = z.real();
  double im = z.imag();

  if (re == 0)
    re = 0;
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
  const std::string allowed_chars = "0123456789+-*=^x. ";
  for (char c : str) {
    if (allowed_chars.find(c) == std::string::npos) {
      throw std::invalid_argument(
          "Обнаружены запрещенные символы. Разрешены только "
          "цифры, математические символы и следующие символы: '+', '-', '*', "
          "'=', '^', 'x', '.'.");
    }
  }

  // Проверка на множественные точки в числах
  regex multiple_dots(R"(\d+\.\d+\.\d+)"); // два или более точек в числе
  if (regex_search(str, multiple_dots)) {
    throw std::invalid_argument("Обнаружены числа с несколькими точками");
  }

  // Проверка на некорректные комбинации символов
  if (regex_search(str, regex(R"(\*[^x])"))) {
    throw std::invalid_argument("Некорректное использование символа '*'");
  }

  if (regex_search(str, regex(R"(\^[^2])"))) {
    throw std::invalid_argument("Некорректное использование символа '^'");
  }

  if (regex_search(str, regex(R"([+-]{2,})"))) {
    throw std::invalid_argument(
        "Некорректная последовательность знаков '+' и '-'");
  }

  bool has_digit = false;
  for (size_t i = 0; i < str.length(); i++) {
    char current_char = str[i];

    if (isdigit(current_char)) {
      has_digit = true;
    }

    if (current_char == '.') {
      if (i == 0 || i == str.length() - 1) {
        throw std::invalid_argument("Некорректное использование точки в числе");
      }
      if (!isdigit(str[i - 1])) {
        throw std::invalid_argument("Перед точкой должна быть цифра");
      }
      if (i + 1 < str.length() && !isdigit(str[i + 1])) {
        throw std::invalid_argument("После точки должна быть цифра");
      }
    }
  }

  if (!has_digit) {
    throw std::invalid_argument("Строка должна содержать хотя бы одну цифру");
  }
}

void C::parseEquationString(const std::string &equationStr) {
  validateEquationString(equationStr);
  std::string simplified = equationStr;

  // Предварительная обработка строки
  std::erase(simplified, ' ');
  std::transform(simplified.begin(), simplified.end(), simplified.begin(),
                 ::tolower);

  std::cout << "Упрощенная строка: " << simplified << std::endl;

  double a = 1.0;
  double b = 0.0;
  double c_val = 0.0;

  // Парсим коэффициенты по очереди
  parseA(simplified, a);
  parseB(simplified, b);
  parseC(simplified, c_val);

  // Проверяем, что уравнение квадратное (есть x^2)
  if (!isAFound(simplified)) {
    throw std::invalid_argument("Не удалось распознать квадратное уравнение. "
                                "Убедитесь, что есть член с x^2");
  }

  // Устанавливаем коэффициенты
  setA(a);
  setB(b);
  setC(c_val);

  std::cout << "Распознанные коэффициенты: a=" << a << ", b=" << b
            << ", c=" << c_val << std::endl;
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

void C::parseC(std::string_view simplified, double &c_val) {
  size_t equal_pos = simplified.find('=');
  if (equal_pos == std::string::npos)
    return;

  std::string before_equal = std::string(simplified.substr(0, equal_pos));
  std::cout << "Остаток перед '=': '" << before_equal << "'" << std::endl;

  // Если после парсинга a и b остались символы кроме допустимых для числа c
  if (!before_equal.empty()) {
    // Допустимые символы для коэффициента c (только число)
    const std::string allowed_c_chars = "+-0123456789.";

    for (char c : before_equal) {
      if (allowed_c_chars.find(c) == std::string::npos) {
        throw std::invalid_argument(
            "Недопустимые символы в свободном члене: '" + before_equal + "'");
      }
    }

    // Проверяем, что это валидное число (не несколько чисел с операциями)
    if (!isValidNumber(before_equal)) {
      throw std::invalid_argument("Свободный член должен быть одним числом: '" +
                                  before_equal + "'");
    }

    c_val = Utils::stringToDouble(before_equal);
    std::cout << "Найден коэффициент c: " << c_val << std::endl;
  }
}

double C::parseNumber(const std::string &num_str, double default_value) {
  if (num_str.empty() || num_str == "+")
    return default_value;
  if (num_str == "-")
    return -default_value;

  try {
    return Utils::stringToDouble(num_str);
  } catch (const std::exception &) {
    throw std::invalid_argument("Некорректный числовой формат: '" + num_str +
                                "'");
  }
}

bool C::isAFound(const string &simplified) {
  // Проверяем наличие x^2 в упрощенной строке
  return simplified.contains("x^2") != string::npos ||
         regex_search(simplified, regex(R"(([+-]?\d+\.?\d*)x\^2)"));
}

bool C::isValidNumber(const std::string &str) {
  if (str.empty())
    return false;

  int dotCount = 0;
  bool hasDigits = false;

  for (size_t i = 0; i < str.length(); i++) {
    char c = str[i];

    if (c == '.') {
      dotCount++;
      if (dotCount > 1)
        return false;
    } else if (c == '-' || c == '+') {
      if (i != 0)
        return false;
    } else if (isdigit(c)) {
      hasDigits = true;
    } else {
      return false;
    }
  }

  return hasDigits && dotCount <= 1;
}