#include "utils.hpp"
#include <cctype>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

double Utils::input(const string &message) {
  if (!message.empty())
    cout << message;

  double number;
  while (true) {
    cin >> number;
    if (cin.fail() || cin.peek() != '\n') {
      cout << "Некорректный ввод. Пожалуйста, введите число: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      break;
    }
  }
  return number;
}

string Utils::inputString(const string &message) {
  if (!message.empty())
    cout << message;

  string str;
  getline(cin, str);
  return str;
}

double Utils::stringToDouble(const std::string &str) {
  if (str.empty()) {
    throw invalid_argument("Пустая строка не может быть преобразована в число");
  }

  string s = str;
  while (!s.empty() && isspace(s[0]))
    s.erase(0, 1);
  while (!s.empty() && isspace(s.back()))
    s.pop_back();

  if (s.empty())
    throw invalid_argument("Строка содержит только пробелы");

  if (s == "+" || s.empty())
    return 1.0;
  if (s == "-")
    return -1.0;

  double result = 0.0;
  double sign = 1.0;
  double fraction = 1.0;
  bool has_digit = false;
  bool has_point = false;
  size_t i = 0;
  if (s[i] == '+')
    i++;
  else if (s[i] == '-') {
    sign = -1.0;
    i++;
  }
  for (; i < s.length(); i++) {
    if (s[i] == '.') {
      if (has_point)
        throw invalid_argument("Несколько точек в числе: " + str);
      has_point = true;
      fraction = 0.1;
    } else if (isdigit(s[i])) {
      has_digit = true;
      if (!has_point)
        result = result * 10.0 + (s[i] - '0');
      else {
        result += (s[i] - '0') * fraction;
        fraction *= 0.1;
      }
    } else
      throw invalid_argument("Недопустимый символ в числе: " + string(1, s[i]));
  }

  if (!has_digit)
    throw invalid_argument("Нет цифр в числе: " + str);
  return sign * result;
}