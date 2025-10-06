#pragma once
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

class Utils {
private:
  static void clearInputBuffer();

  template <class T>
  static T inputNumber(const string &message, const string &errorMsg) {
    if (!message.empty())
      cout << message;

    T number;
    while (true) {
      cin >> number;
      if (cin.fail() || cin.peek() != '\n') {
        cout << errorMsg;
        Utils::clearInputBuffer();
      } else {
        Utils::clearInputBuffer();
        return number;
      }
    }
  }

  template <class T, class InputFunc>
  static T positiveInput(const string &message, T max_value,
                         const string &errorMessage, InputFunc inputFunc) {
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

public:
  static void clearScreen();
  static int inputInteger(const string &message = "");
  static double inputDouble(const string &message = "");
  static size_t inputSize(const string &message, bool allow_zero = false);
  static int positiveInputInteger(
      const string &message = "", int max_value = 0,
      const string &errorMessage = "Внимание! Введите положительное число: ");
  static double positiveInputDouble(
      const string &message = "", double max_value = 0.0,
      const string &errorMessage = "Внимание! Введите положительное число: ");
  static string inputString(const string &message = "");

  Utils() = delete;
  ~Utils() = delete;
};