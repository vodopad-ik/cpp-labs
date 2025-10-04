#include "utils.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
using namespace std;

void clearScreen() {
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

int inputInteger(const string &message) {
  if (!message.empty()) {
    cout << message;
  }
  int number;
  while (true) {
    cin >> number;
    if (cin.fail() || cin.peek() != '\n') {
      cout << "Некорректный ввод. Пожалуйста, введите только целое число.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      break;
    }
  }
  return number;
}

double inputDouble(const string &message) {
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

int positiveInputInteger(const string &message, int max_value,
                         const string &errorMessage) {
  int value;
  do {
    if (!message.empty()) {
      cout << message;
    }
    value = inputInteger();

    if (value <= 0) {
      cout << "Внимание! Введите положительное число: ";
    } else if (max_value > 0 && value > max_value) {
      cout << errorMessage;
    }
  } while (value <= 0 || (max_value > 0 && value > max_value));
  return value;
}

double positiveInputDouble(const string &message, double max_value,
                           const string &errorMessage) {
  double value;
  do {
    if (!message.empty()) {
      cout << message;
    }
    value = inputDouble();

    if (value <= 0) {
      cout << "Внимание! Введите положительное число: ";
    } else if (max_value > 0 && value > max_value) {
      cout << errorMessage;
    }
  } while (value <= 0 || (max_value > 0 && value > max_value));
  return value;
}

string inputOnlyLetters(const string &message) {
  string str;
  while (true) {
    if (!message.empty()) {
      cout << message;
    }
    if (cin.peek() == '\n') {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    getline(cin, str);

    bool allLetters = true;
    bool hasMeaningfulChars = false;

    for (char c : str) {
      if (c == ' ' || c == '-')
        continue;

      if (isdigit(c) || ispunct(c)) {
        allLetters = false;
        break;
      }
      hasMeaningfulChars = true;
    }

    if (allLetters && hasMeaningfulChars) {
      return str;
    } else {
      cout << "Некорректный ввод. Введите только буквы (и пробелы): ";
    }
  }
}