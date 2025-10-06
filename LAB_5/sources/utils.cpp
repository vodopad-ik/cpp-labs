#include "utils.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
using namespace std;

void clearInputBuffer() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

template <typename T>
T inputNumber(const string &message, const string &errorMsg) {
  if (!message.empty()) 
    cout << message;

  T number;
  while (true) {
    cin >> number;
    if (cin.fail() || cin.peek() != '\n') {
      cout << errorMsg;
      clearInputBuffer();
    } else {
      clearInputBuffer();
      return number;
    }
  }
}

int inputInteger(const string &message) {
  return inputNumber<int>(
      message, "Некорректный ввод. Пожалуйста, введите только целое число: ");
}

double inputDouble(const string &message) {
  return inputNumber<double>(message,
                             "Некорректный ввод. Пожалуйста, введите число: ");
}

size_t inputSize(const string &message, bool allowZero) {
  if (!message.empty())
    cout << message;

  long long number;
  while (true) {
    cin >> number;
    if (cin.fail() || cin.peek() != '\n') {
      cout << "Некорректный ввод. Пожалуйста, введите только целое число: ";
      clearInputBuffer();
    } else if (number < 0) {
      cout << "Размер не может быть отрицательным. Попробуйте снова: ";
    } else if (!allowZero && number == 0) {
      cout << "Размер должен быть положительным числом. Попробуйте снова: ";
    } else {
      clearInputBuffer();
      return static_cast<size_t>(number);
    }
  }
}

char inputChar(const string &message) {
  if (!message.empty())
    cout << message;

  char ch;
  while (true) {
    cin >> ch;
    if (cin.fail() || cin.peek() != '\n') {
      cout << "Некорректный ввод. Пожалуйста, введите только один символ: ";
      clearInputBuffer();
    } else {
      clearInputBuffer();
      return ch;
    }
  }
}

template <typename T>
T positiveInput(const string &message, T max_value, const string &errorMessage,
                T (*inputFunc)(const string &)) {
  T value;
  do {
    value = inputFunc(message);

    if (value <= 0)
      cout << "Внимание! Введите положительное число: ";
    else if (max_value > 0 && value > max_value)
      cout << errorMessage;

  } while (value <= 0 || (max_value > 0 && value > max_value));
  return value;
}

int positiveInputInteger(const string &message, int max_value,
                         const string &errorMessage) {
  return positiveInput<int>(message, max_value, errorMessage, inputInteger);
}

double positiveInputDouble(const string &message, double max_value,
                           const string &errorMessage) {
  return positiveInput<double>(message, max_value, errorMessage, inputDouble);
}

string inputString(const string &message) {
  if (!message.empty())
    cout << message;

  string str;
  while (true) {
    getline(cin, str);
    if (cin.fail()) {
      cout << "Ошибка ввода. Попробуйте снова: ";
      clearInputBuffer();
    } else if (str.empty())
      cout << "Строка не может быть пустой. Попробуйте снова: ";
    else
      return str;
  }
}

string inputOnlyLetters(const string &message) {
  string str = inputString(message);
  for (char c : str) {
    if (!isalpha(c) && c != ' ' && c != '-') {
      cout << "Строка должна содержать только буквы, пробелы и дефисы. "
              "Попробуйте снова: ";
      return inputOnlyLetters();
    }
  }
  return str;
}