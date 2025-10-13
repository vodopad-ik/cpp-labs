#include "carValidNumber.hpp"
#include <algorithm>
#include <iostream>
#include <string_view> // Добавлено для более чистого использования find

const std::string CarNumber::validLetters = "ABEIKMNOPCTX";
const std::string CarNumber::validDigits = "0123456789";


bool CarNumber::isValidDigit(char c) {
  return validDigits.find(c) != std::string::npos;
}

bool CarNumber::isValidLetter(char c) {
  char upperC = std::toupper(c);
  return validLetters.find(upperC) != std::string::npos;
}

void CarNumber::displayTemplate() {
  std::cout << "Формат: 1234AB или 1234AB1" << std::endl;
  std::cout << "Допустимые буквы: A B E I K M N O P C T X" << std::endl;
}

bool CarNumber:: checkLength(const std::string &formatted) {
  if (formatted.length() < 6 || formatted.length() > 7) {
    std::cout << "Ошибка: номер должен содержать 6 или 7 символов!"
              << std::endl;
    return false;
  }
  return true;
}

bool CarNumber:: checkFirstFourDigits(const std::string &formatted) {
  for (int i = 0; i < 4; i++) {
    if (!CarNumber::isValidDigit(formatted[i])) {
      std::cout << "Ошибка: первые 4 символа должны быть цифрами!" << std::endl;
      return false;
    }
  }
  return true;
}

bool CarNumber::checkLetters(const std::string &formatted,
                         const std::string &validLetters) {
  for (int i = 4; i < 6; i++) {
    if (!CarNumber::isValidLetter(formatted[i])) {
      std::cout << "Ошибка: символы 5-6 должны быть буквами из списка: "
                << validLetters << std::endl;
      return false;
    }
  }
  return true;
}

bool CarNumber::checkRegionCode(const std::string &formatted) {
  if (formatted.length() == 7 &&
      (!CarNumber::isValidDigit(formatted[6]) || formatted[6] == '0')) {
    std::cout << "Ошибка: код региона должен быть цифрой от 1 до 9!"
              << std::endl;
    return false;
  }
  return true;
}

std::string CarNumber::inputLicensePlate(const std::string &message) {
  std::string plate;
  bool valid = false;

  while (!valid) {
    std::cout << message;
    displayTemplate();
    std::getline(std::cin, plate);

    std::string formatted;
    for (char c : plate) {
      if (c != ' ' && c != '-')
        formatted += std::toupper(c);
    }
    if (!checkLength(formatted))
      continue;
    if (!checkFirstFourDigits(formatted))
      continue;
    if (!checkLetters(formatted, validLetters))
      continue;
    if (!checkRegionCode(formatted))
      continue;

    valid = true;
    plate = formatted;
  }

  std::string result;
  for (int i = 0; i < plate.length(); i++) {
    result += plate[i];
    if (i == 3)
      result += " ";
  }
  std::cout << "Принят номер: " << result << std::endl;
  return plate;
}