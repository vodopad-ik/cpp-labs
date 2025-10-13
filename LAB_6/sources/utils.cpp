#include "utils.hpp"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

double input(const string &message) {
  if (!message.empty()) {
    cout << message;
  }

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

string inputEquationString(const string &message) {
  if (!message.empty())
    cout << message;
  string str;
  getline(cin, str);

  size_t start = str.find_first_not_of(" \t");
  if (size_t end = str.find_last_not_of(" \t");
      start != string::npos && end != string::npos)
    str = str.substr(start, end - start + 1);
  return str;
}