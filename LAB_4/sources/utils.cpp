#include "utils.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>

void Utils::clearScreen() {
#ifdef _WIN32
  std::system("cls");
#else
  std::system("clear");
#endif
}

int Utils::inputInteger(const std::string &message) {
  if (!message.empty()) {
    std::cout << message;
  }
  int number;
  while (true) {
    std::cin >> number;
    if (std::cin.fail() || std::cin.peek() != '\n') {
      std::cout
          << "Некорректный ввод. Пожалуйста, введите только целое число.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      break;
    }
  }
  return number;
}

double Utils::inputDouble(const std::string &message) {
  if (!message.empty()) {
    std::cout << message;
  }

  double number;
  while (true) {
    std::cin >> number;
    if (std::cin.fail() || std::cin.peek() != '\n') {
      std::cout << "Некорректный ввод. Пожалуйста, введите число: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    }
  }
  return number;
}

int Utils::positiveInputInteger(const std::string &message, int max_value,
                                const std::string &errorMessage) {
  int value;
  do {
    if (!message.empty()) {
      std::cout << message;
    }
    value = inputInteger();

    if (value <= 0) {
      std::cout << "Внимание! Введите положительное число: ";
    } else if (max_value > 0 && value > max_value) {
      std::cout << errorMessage;
    }
  } while (value <= 0 || (max_value > 0 && value > max_value));
  return value;
}

double Utils::positiveInputDouble(const std::string &message, double max_value,
                                  const std::string &errorMessage) {
  double value;
  do {
    if (!message.empty()) {
      std::cout << message;
    }
    value = inputDouble();

    if (value <= 0) {
      std::cout << "Внимание! Введите положительное число: ";
    } else if (max_value > 0 && value > max_value) {
      std::cout << errorMessage;
    }
  } while (value <= 0 || (max_value > 0 && value > max_value));
  return value;
}

std::string Utils::inputOnlyLetters(const std::string &message) {
  std::string str;
  while (true) {
    if (!message.empty()) {
      std::cout << message;
    }
    if (std::cin.peek() == '\n') {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::getline(std::cin, str);

    bool allLetters = true;
    bool hasMeaningfulChars = false;

    for (char c : str) {
      if (c == ' ' || c == '-')
        continue;

      if (std::isdigit(c) || std::ispunct(c)) {
        allLetters = false;
        break;
      }
      hasMeaningfulChars = true;
    }

    if (allLetters && hasMeaningfulChars) {
      return str;
    } else {
      std::cout << "Некорректный ввод. Введите только буквы (и пробелы): ";
    }
  }
}