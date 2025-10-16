#include "parser.hpp"
#include "utils.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

double Parser::parseNumber(const string &num_str, double default_value) {
  if (num_str.empty() || num_str == "+")
    return default_value;
  if (num_str == "-")
    return -default_value;
  try {
    return Utils::stringToDouble(num_str);
  } catch (const exception &) {
    throw InvalidNumberFormatException("'" + num_str + "'");
  }
}

string Parser::validateEquationString(const string &str) {
  validateAllowedChars(str);
  string simplified = simplifyString(str);

  validateBasicStructure(simplified);
  validateRegexPatterns(str);
  validateDigitsAndDots(str);
  return simplified;
}

void Parser::validateAllowedChars(const string &str) {
  const string allowed_chars = "0123456789+-*=^x. ";
  for (char c : str) {
    if (!allowed_chars.contains(c)) {
      throw InvalidCharacterException(
          "Обнаружены запрещенные символы. Разрешены только "
          "цифры и следующие символы: '+', '-', '*', "
          "'=', '^', 'x', '.'.");
    }
  }
}

std::string Parser::simplifyString(const std::string &str) {
  string simplified = str;
  std::erase(simplified, ' ');
  std::ranges::transform(simplified, simplified.begin(), ::tolower);
  return simplified;
}

void Parser::validateBasicStructure(const string &simplified) {
  if (!simplified.contains("x^2")) {
    throw InvalidEquationException(
        "Это не квадратное уравнение. Должен быть член с x^2");
  }

  if (!simplified.contains('='))
    throw InvalidEquationException("Уравнение должно содержать знак '='");
  if (std::regex_search(simplified, std::regex(R"(x\^2\d)"))) {
    throw InvalidEquationException(
        "Некорректный формат: после x^2 не должно быть цифр без оператора");
  }
}

void Parser::validateRegexPatterns(const std::string &str) {
  const std::vector<std::pair<std::regex, std::string>> patterns = {
      {std::regex(R"(\d+\.\d+\.\d+)"),
       "Обнаружены числа с несколькими точками"},
      {std::regex(R"(\*[^x])"), "Некорректное использование символа '*'"},
      {std::regex(R"(\^[^2])"), "Некорректное использование символа '^'"},
      {std::regex(R"([+-]{2,})"),
       "Некорректная последовательность знаков '+' и '-'"}};

  for (const auto &[pattern, error_msg] : patterns) {
    if (regex_search(str, pattern))
      throw InvalidEquationException(error_msg);
  }
}

void Parser::validateDigitsAndDots(const std::string &str) {
  bool has_digit = false;
  for (size_t i = 0; i < str.length(); i++) {
    char current_char = str[i];
    if (isdigit(current_char))
      has_digit = true;
    if (current_char == '.')
      validateDotPosition(str, i);
  }

  if (!has_digit)
    throw InvalidEquationException("Строка должна содержать хотя бы одну цифру");
}

void Parser::validateDotPosition(const std::string &str, size_t pos) {
  if (pos == 0 || pos == str.length() - 1)
    throw InvalidNumberFormatException("Некорректное использование точки в числе");
  if (!isdigit(str[pos - 1]))
    throw InvalidNumberFormatException("Перед точкой должна быть цифра");
  if (pos + 1 < str.length() && !isdigit(str[pos + 1]))
    throw InvalidNumberFormatException("После точки должна быть цифра");
}

void Parser::parseEquationString(const std::string &equationStr, double &a,
                                 double &b, double &c) {
  string simplified = validateEquationString(equationStr);
  a = 1.0;
  b = 0.0;
  c = 0.0;
  parseA(simplified, a);
  parseB(simplified, b);
  parseC(simplified, c);

  if (!isAFound(equationStr))
    throw InvalidEquationException("Не удалось распознать квадратное уравнение. "
                           "Убедитесь, что есть член с x^2");

  cout << "Распознанные коэффициенты: a=" << a << ", b=" << b << ", c=" << c
       << endl;
}

void Parser::parseA(string &simplified, double &a) {
  std::regex a_pattern(R"(([+-]?\d*\.?\d+)x\^2)");
  std::smatch a_match;

  if (std::regex_search(simplified, a_match, a_pattern) && a_match.size() > 1) {
    std::string a_str = a_match[1].str();
    a = parseNumber(a_str, 1.0);
    simplified = std::regex_replace(simplified, a_pattern, "");
  } else {
    std::regex x2_default_pattern(R"(([+-]?)x\^2)");
    if (std::regex_search(simplified, a_match, x2_default_pattern) &&
        a_match.size() > 1) {
      std::string sign = a_match[1].str();
      a = (sign == "-") ? -1.0 : 1.0;
      simplified = std::regex_replace(simplified, x2_default_pattern, "");
    }
  }
}

void Parser::parseB(string &simplified, double &b) {
  std::regex b_pattern(R"(([+-]?\d*\.?\d*)x(?!\^))");
  std::smatch b_match;
  if (std::regex_search(simplified, b_match, b_pattern) && b_match.size() > 1) {
    std::string b_str = b_match[1].str();
    b = parseNumber(b_str, 1.0);
    simplified = std::regex_replace(simplified, b_pattern, "");
  }
}

void Parser::parseC(const std::string &simplified, double &c_val) {
  if (!simplified.contains('='))
    return;
  std::regex equal_pattern(R"((.*)=(.*))");
  std::smatch match;

  if (std::regex_match(simplified, match, equal_pattern) && match.size() == 3) {
    std::string left_part = match[1].str();
    std::string right_part = match[2].str();
    double left_c = 0.0;
    if (!left_part.empty()) {
      if (left_part == "+")
        left_c = 1.0;
      else if (left_part == "-")
        left_c = -1.0;
      else if (isValidNumber(left_part))
        left_c = Utils::stringToDouble(left_part);
      else if (!left_part.empty())
        throw InvalidEquationException(
            "Недопустимые символы в свободном члене слева: '" + left_part +
            "'");
    }
    double right_c = 0.0;
    if (!right_part.empty()) {
      if (right_part == "+")
        right_c = 1.0;
      else if (right_part == "-")
        right_c = -1.0;
      else if (isValidNumber(right_part))
        right_c = Utils::stringToDouble(right_part);
      else if (!right_part.empty())
        throw InvalidEquationException(
            "Недопустимые символы в свободном члене справа: '" + right_part +
            "'");
    }
    c_val = left_c - right_c;
  }
}

bool Parser::isAFound(const std::string &simplified) {
  std::string temp = simplified;
  std::erase(temp, ' ');
  std::ranges::transform(temp, temp.begin(), ::tolower);
  return temp.contains("x^2");
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
      if (i != 0)
        return false;
    } else if (isdigit(c))
      hasDigits = true;
    else
      return false;
  }
  return hasDigits;
}