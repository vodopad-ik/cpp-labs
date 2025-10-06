#include "utils.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>

void Utils::clearInputBuffer() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Utils::clearScreen() {
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

int Utils::inputInteger(const std::string &message) {
  return inputNumber<int>(
      message, "Некорректный ввод. Пожалуйста, введите только целое число: ");
}

double Utils::inputDouble(const std::string &message) {
  return inputNumber<double>(message,
                             "Некорректный ввод. Пожалуйста, введите число: ");
}

size_t Utils::inputSize(const std::string &message, bool allowZero) {
  if (!message.empty())
    std::cout << message;

  long long number;
  while (true) {
    std::cin >> number;
    if (std::cin.fail() || std::cin.peek() != '\n') {
      std::cout
          << "Некорректный ввод. Пожалуйста, введите только целое число: ";
      clearInputBuffer();
    } else if (number < 0) {
      std::cout << "Размер не может быть отрицательным. Попробуйте снова: ";
    } else if (!allowZero && number == 0) {
      std::cout
          << "Размер должен быть положительным числом. Попробуйте снова: ";
    } else {
      clearInputBuffer();
      return static_cast<size_t>(number);
    }
  }
}

int Utils::positiveInputInteger(const std::string &message, int max_value,
                                const std::string &errorMessage) {
  return positiveInput<int>(
      message, max_value, errorMessage,
      [](const std::string &msg) { return inputInteger(msg); });
}

double Utils::positiveInputDouble(const std::string &message, double max_value,
                                  const std::string &errorMessage) {
  return positiveInput<double>(
      message, max_value, errorMessage,
      [](const std::string &msg) { return inputDouble(msg); });
}

std::string Utils::inputString(const std::string &message) {
  if (!message.empty())
    std::cout << message;

  std::string str;
  while (true) {
    std::getline(std::cin, str);
    if (std::cin.fail()) {
      std::cout << "Ошибка ввода. Попробуйте снова: ";
      clearInputBuffer();
    } else if (str.empty()) {
      std::cout << "Строка не может быть пустой. Попробуйте снова: ";
    } else {
      return str;
    }
  }
}