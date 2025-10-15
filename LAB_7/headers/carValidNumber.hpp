#pragma once
#include <iostream>
#include <string>
#include <string_view>

class CarNumber {
private:
  static const std::string valid_letters;
  static const std::string valid_digits;

  static bool isValidDigit(char c);
  static bool isValidLetter(char c);

  static bool checkLength(std::string_view formatted);
  static bool checkFirstFourDigits(std::string_view formatted);
  static bool checkLetters(std::string_view formatted);
  static bool checkRegionCode(std::string_view formatted);

  static void displayTemplate();

public:
  static std::string
  inputLicensePlate(const std::string &message = "Введите номер машины: ");
};