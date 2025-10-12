#include "utils.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>

void Utils::clearInputBuffer() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Utils:: clearScreen() { 
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

int Utils::positiveInputInteger(const std::string &message, int min_value,
                                int max_value,
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

bool Utils::isCyrillicChar(unsigned char c) {
    return (c >= 0xD0 && c <= 0xD1) || (c >= 0xD2 && c <= 0xD3);
}

std::string Utils::inputOnlyLetters(const std::string &message) {
  std::string str;
  while (true) {
    if (!message.empty())
      std::cout << message;
    if (std::cin.peek() == '\n')
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::getline(std::cin, str);

    bool allValidChars = true;
    bool hasMeaningfulChars = false;

    for (size_t i = 0; i < str.length(); i++) {
      unsigned char c = str[i];
      
      // Разрешаем пробелы и дефисы
      if (c == ' ' || c == '-')
        continue;

      // Проверяем латинские буквы
      bool isLatinLetter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
      
      // Проверяем кириллические символы (UTF-8)
      bool isCyrillic = isCyrillicChar(c);
      
      // Проверяем цифры
      bool isDigit = (c >= '0' && c <= '9');
      
      // Проверяем пунктуацию (кроме дефиса, который уже разрешен)
      bool isPunctuation = std::ispunct(c) && c != '-';

      if (isDigit || isPunctuation) {
        allValidChars = false;
        break;
      }
      
      // Если символ не латинская буква и не кириллический - невалидный
      if (!isLatinLetter && !isCyrillic) {
        allValidChars = false;
        break;
      }
      
      hasMeaningfulChars = true;
      
      // Пропускаем второй байт UTF-8 символов кириллицы
      if (isCyrillic && i + 1 < str.length()) {
        i++; // Пропускаем следующий байт UTF-8 символа
      }
    }

    if (allValidChars && hasMeaningfulChars) {
      return str;
    } else {
      std::cout << "Некорректный ввод. Введите только буквы (русские, английские и пробелы): ";
    }
  }
}

int Utils::inputIntegerInRange(const std::string &message, int min_value,
                               int max_value, const std::string &errorMessage) {
  if (!message.empty())
    std::cout << message;

  int number;
  while (true) {
    std::cin >> number;
    if (std::cin.fail() || std::cin.peek() != '\n') {
      std::cout << "Некорректный ввод. Пожалуйста, введите целое число: ";
      clearInputBuffer();
    } else if (number < min_value || number > max_value) {
      std::cout << errorMessage;
      std::cout << "Допустимый диапазон: от " << min_value << " до "
                << max_value << ". Попробуйте снова: ";
    } else {
      clearInputBuffer();
      return number;
    }
  }
}