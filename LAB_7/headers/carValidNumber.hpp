#pragma once
#include <iostream>
#include <string>
#include <string_view> // Включаем для std::string_view

class CarNumber {
private:
  static const std::string validLetters;
  static const std::string validDigits;

  static bool isValidDigit(char c);
  static bool isValidLetter(char c);

  // Обновлена сигнатура: const std::string& заменено на std::string_view
  static bool checkLength(std::string_view formatted);
  static bool checkFirstFourDigits(std::string_view formatted);
  
  // Обновлена сигнатура: удален второй аргумент (validLetters)
  static bool checkLetters(std::string_view formatted);
  static bool checkRegionCode(std::string_view formatted);

  static void displayTemplate();

public:
  static std::string
  inputLicensePlate(const std::string &message = "Введите номер машины: ");
};