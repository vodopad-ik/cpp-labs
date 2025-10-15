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

int Utils::inputInt(const std::string &message) {
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

bool Utils::inputInt(int &result, const std::string &message) {
  if (!message.empty()) 
    std::cout << message;
  std::string input;
  std::getline(std::cin, input);
  if (input.empty()) 
    return false;
  try {
    size_t pos;
    result = std::stoi(input, &pos);
    if (pos != input.length()) {
      std::cout
          << "Некорректный ввод. Пожалуйста, введите только целое число.\n";
      return inputInt(result, message);
    }
    return true;
  } catch (const std::exception &e) {
    std::cout << "Некорректный ввод. Пожалуйста, введите целое число.\n";
    return inputInt(result, message);
  }
}

int Utils::inputIntInRange(const std::string &message, int min_value,
                           int max_value, const std::string &errorMessage) {
  if (!message.empty())
  std::cout << message;
  while (true) {
    int number;
    if (inputInt(number, "")) {
      if (number < min_value || number > max_value) {
        std::cout << errorMessage;
        std::cout << "Допустимый диапазон: от " << min_value << " до "
                  << max_value << ". Попробуйте снова: ";
      } else
        return number;
    } else {
      std::cout
          << "Ввод не может быть пустым. Пожалуйста, выберите пункт меню: ";
    }
  }
}