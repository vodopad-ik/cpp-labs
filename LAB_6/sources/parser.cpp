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

std::string Parser::validateEquationString(const std::string &str) {
    validateAllowedChars(str);
    string simplified = simplifyString(str);
    
    validateBasicStructure(simplified);
    validateRegexPatterns(str);
    validateDigitsAndDots(str);
    
    return simplified;
}

void Parser::validateAllowedChars(const std::string &str) {
    const std::string allowed_chars = "0123456789+-*=^x. ";
    for (char c : str) {
        if (allowed_chars.find(c) == std::string::npos) {
            throw std::invalid_argument(
                "Обнаружены запрещенные символы. Разрешены только "
                "цифры и следующие символы: '+', '-', '*', "
                "'=', '^', 'x', '.'.");
        }
    }
}

std::string Parser::simplifyString(const std::string &str) {
    string simplified = str;
    simplified.erase(std::remove(simplified.begin(), simplified.end(), ' '), simplified.end());
    std::transform(simplified.begin(), simplified.end(), simplified.begin(), ::tolower);
    return simplified;
}

void Parser::validateBasicStructure(const std::string &simplified) {
    if (!simplified.contains("x^2")) {
        throw std::invalid_argument("Это не квадратное уравнение. Должен быть член с x^2");
    }
    
    if (!simplified.contains('=')) {
        throw std::invalid_argument("Уравнение должно содержать знак '='");
    }
    
    if (std::regex_search(simplified, std::regex(R"(x\^2\d)"))) {
        throw std::invalid_argument("Некорректный формат: после x^2 не должно быть цифр без оператора");
    }
}

void Parser::validateRegexPatterns(const std::string &str) {
    const std::vector<std::pair<std::regex, std::string>> patterns = {
        {std::regex(R"(\d+\.\d+\.\d+)"), "Обнаружены числа с несколькими точками"},
        {std::regex(R"(\*[^x])"), "Некорректное использование символа '*'"},
        {std::regex(R"(\^[^2])"), "Некорректное использование символа '^'"},
        {std::regex(R"([+-]{2,})"), "Некорректная последовательность знаков '+' и '-'"}
    };
    
    for (const auto& [pattern, error_msg] : patterns) {
        if (regex_search(str, pattern)) {
            throw std::invalid_argument(error_msg);
        }
    }
}

void Parser::validateDigitsAndDots(const std::string &str) {
    bool has_digit = false;
    
    for (size_t i = 0; i < str.length(); i++) {
        char current_char = str[i];
        
        if (isdigit(current_char)) {
            has_digit = true;
        }
        
        if (current_char == '.') {
            validateDotPosition(str, i);
        }
    }
    
    if (!has_digit) {
        throw std::invalid_argument("Строка должна содержать хотя бы одну цифру");
    }
}

void Parser::validateDotPosition(const std::string &str, size_t pos) {
    if (pos == 0 || pos == str.length() - 1) {
        throw std::invalid_argument("Некорректное использование точки в числе");
    }
    
    if (!isdigit(str[pos - 1])) {
        throw std::invalid_argument("Перед точкой должна быть цифра");
    }
    
    if (pos + 1 < str.length() && !isdigit(str[pos + 1])) {
        throw std::invalid_argument("После точки должна быть цифра");
    }
}

void Parser::parseEquationString(const std::string &equationStr, double &a,
                                 double &b, double &c) {
  string simplified = validateEquationString(equationStr);

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
  std::regex a_pattern(R"(([+-]?\d*\.?\d+)x\^2)");
  std::smatch a_match;

  if (std::regex_search(simplified, a_match, a_pattern) && a_match.size() > 1) {
    std::string a_str = a_match[1].str();
    std::cout << "Найден коэффициент a: '" << a_str << "'" << std::endl;

    a = parseNumber(a_str, 1.0);
    simplified = std::regex_replace(simplified, a_pattern, "");
    std::cout << "Строка после удаления a: " << simplified << std::endl;
  } else {
    // Если не нашли явный коэффициент, проверяем наличие x^2 без коэффициента
    // НО ТОЛЬКО ЕСЛИ ЕСТЬ ТОЧНО "x^2", а не просто "x" или цифры
    std::regex x2_default_pattern(R"(([+-]?)x\^2)");
    if (std::regex_search(simplified, a_match, x2_default_pattern) &&
        a_match.size() > 1) {
      std::string sign = a_match[1].str();
      a = (sign == "-") ? -1.0 : 1.0;
      std::cout << "Найден коэффициент a по умолчанию: " << a << std::endl;
      simplified = std::regex_replace(simplified, x2_default_pattern, "");
      std::cout << "Строка после удаления a: " << simplified << std::endl;
    }
    // Если не нашли x^2 вообще - НИЧЕГО НЕ ДЕЛАЕМ, a остается 1.0
    // Ошибка уже должна быть поймана в validateEquationString
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
  // Проверяем наличие знака равенства
  if (!simplified.contains('='))
    return;

  // Разделяем на левую и правую части используя regex
  std::regex equal_pattern(R"((.*)=(.*))");
  std::smatch match;

  if (std::regex_match(simplified, match, equal_pattern) && match.size() == 3) {
    std::string left_part = match[1].str();
    std::string right_part = match[2].str();

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
            "Недопустимые символы в свободном члене слева: '" + left_part +
            "'");
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