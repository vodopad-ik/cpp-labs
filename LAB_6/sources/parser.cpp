#include "parser.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

double Parser::parseNumber(const std::string &num_str, double default_value) {
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

void Parser::validateEquationString(const std::string &str) {
  const std::string allowed_chars = "0123456789+-*=^x. ";
  for (char c : str) {
    if (allowed_chars.find(c) == std::string::npos) {
      throw std::invalid_argument(
          "Обнаружены запрещенные символы. Разрешены только "
          "цифры и следующие символы: '+', '-', '*', "
          "'=', '^', 'x', '.'.");
    }
  }
  string simplified = str;
  simplified.erase(std::remove(simplified.begin(), simplified.end(), ' '),
                   simplified.end());
  std::transform(simplified.begin(), simplified.end(), simplified.begin(),
                 ::tolower);

  bool has_x2 = simplified.find("x^2") != std::string::npos;
  bool has_equals = simplified.find('=') != std::string::npos;


  if (!has_x2) {
    throw std::invalid_argument(
        "Это не квадратное уравнение. Должен быть член с x^2");
  }

  if (!has_equals) {
    throw std::invalid_argument("Уравнение должно содержать знак '='");
  }
  if (std::regex_search(simplified, std::regex(R"(x\^2\d)"))) {
    throw std::invalid_argument(
        "Некорректный формат: после x^2 не должно быть цифр без оператора");
  }

  // Проверка на множественные точки в числах
  std::regex multiple_dots(R"(\d+\.\d+\.\d+)");
  if (regex_search(str, multiple_dots)) {
    throw std::invalid_argument("Обнаружены числа с несколькими точками");
  }

  // Проверка на некорректные комбинации символов
  if (regex_search(str, std::regex(R"(\*[^x])"))) {
    throw std::invalid_argument("Некорректное использование символа '*'");
  }

  if (regex_search(str, std::regex(R"(\^[^2])"))) {
    throw std::invalid_argument("Некорректное использование символа '^'");
  }

  if (regex_search(str, std::regex(R"([+-]{2,})"))) {
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

void Parser::parseEquationString(const std::string &equationStr, double &a,
                                 double &b, double &c) {
  validateEquationString(equationStr);
  string simplified = equationStr;

  // Предварительная обработка строки
  simplified.erase(remove(simplified.begin(), simplified.end(), ' '),
                   simplified.end());
  transform(simplified.begin(), simplified.end(), simplified.begin(),
            ::tolower);

  cout << "Упрощенная строка: " << simplified << endl;

  a = 1.0;
  b = 0.0;
  c = 0.0;

  // Парсим коэффициенты по очереди
  parseA(simplified, a);
  parseB(simplified, b);
  parseC(simplified, c);

  // Дополнительная проверка: убеждаемся что нашли x^2
  if (!isAFound(equationStr)) {
    throw invalid_argument("Не удалось распознать квадратное уравнение. "
                           "Убедитесь, что есть член с x^2");
  }

  cout << "Распознанные коэффициенты: a=" << a << ", b=" << b << ", c=" << c
       << endl;
}

void Parser::parseA(string &simplified, double &a) {
  std::regex a_pattern(R"(([+-]?\d*\.?\d+)x\^2)"); // исправлено: \d* вместо \d+
  std::smatch a_match;

  if (std::regex_search(simplified, a_match, a_pattern) && a_match.size() > 1) {
    std::string a_str = a_match[1].str();
    std::cout << "Найден коэффициент a: '" << a_str << "'" << std::endl;

    a = parseNumber(a_str, 1.0);
    simplified = std::regex_replace(simplified, a_pattern, "");
    std::cout << "Строка после удаления a: " << simplified << std::endl;
  } else {
    // Если не нашли явный коэффициент, проверяем наличие x^2 без коэффициента
    if (simplified.contains("x^2") != std::string::npos) {
      a = 1.0; // коэффициент по умолчанию
      simplified = std::regex_replace(simplified, std::regex(R"(x\^2)"), "");
      std::cout << "Найден коэффициент a по умолчанию: 1.0" << std::endl;
    }
  }
}

void Parser::parseB(string &simplified, double &b) {
  // Парсим только если после парсинга a остался x (не x^2)
  std::regex b_pattern(R"(([+-]?\d*\.?\d*)x(?!\^))");
  std::smatch b_match;

  if (std::regex_search(simplified, b_match, b_pattern) && b_match.size() > 1) {
    std::string b_str = b_match[1].str();
    std::cout << "Найден коэффициент b: '" << b_str << "'" << std::endl;

    b = parseNumber(b_str, 1.0);
    simplified = std::regex_replace(simplified, b_pattern, "");
    std::cout << "Строка после удаления b: " << simplified << std::endl;
  }
}

void Parser::parseC(std::string &simplified, double &c_val) {
  // Находим позицию знака равенства
  size_t equal_pos = simplified.find('=');
  if (equal_pos == std::string::npos)
    return;

  // Разделяем на левую и правую части
  std::string left_part = simplified.substr(0, equal_pos);
  std::string right_part = simplified.substr(equal_pos + 1);

  std::cout << "Левая часть: '" << left_part << "'" << std::endl;
  std::cout << "Правая часть: '" << right_part << "'" << std::endl;

  // Обрабатываем левую часть (свободные члены)
  double left_c = 0.0;
  if (!left_part.empty()) {
    if (left_part == "+") {
      left_c = 1.0;
    } else if (left_part == "-") {
      left_c = -1.0;
    } else if (isValidNumber(left_part)) {
      left_c = Utils::stringToDouble(left_part);
    } else if (!left_part.empty()) {
      throw std::invalid_argument(
          "Недопустимые символы в свободном члене слева: '" + left_part + "'");
    }
  }

  // Обрабатываем правую часть (свободные члены)
  double right_c = 0.0;
  if (!right_part.empty()) {
    if (right_part == "+") {
      right_c = 1.0;
    } else if (right_part == "-") {
      right_c = -1.0;
    } else if (isValidNumber(right_part)) {
      right_c = Utils::stringToDouble(right_part);
    } else if (!right_part.empty()) {
      throw std::invalid_argument(
          "Недопустимые символы в свободном члене справа: '" + right_part +
          "'");
    }
  }

  // Переносим все в левую часть: c = left_c - right_c
  c_val = left_c - right_c;
  std::cout << "Найден коэффициент c: " << c_val << " (слева: " << left_c
            << ", справа: " << right_c << ")" << std::endl;
}

bool Parser::isAFound(const std::string &simplified) {
  // Проверяем наличие x^2 в оригинальной строке (до парсинга)
  std::string temp = simplified;
  temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
  std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

  return temp.contains("x^2") != std::string::npos;
}

bool Parser::isValidNumber(const std::string &str) {
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
      // Знак может быть только в начале
      if (i != 0)
        return false;
    } else if (isdigit(c)) {
      hasDigits = true;
    } else {
      return false;
    }
  }

  return hasDigits;
}