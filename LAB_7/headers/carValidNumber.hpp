#pragma once
#include <iostream>
#include <string>

class CarNumber {
private:
  static const std::string validLetters;
  static const std::string validDigits;

  static bool isValidDigit(char c);
  static bool isValidLetter(char c);

  static bool checkLength(const std::string &formatted);
  static bool checkFirstFourDigits(const std::string &formatted);
  static bool checkLetters(const std::string &formatted,
                           const std::string &validLetters);
  static bool checkRegionCode(const std::string &formatted);

  static void displayTemplate();

public:
  static std::string
  inputLicensePlate(const std::string &message = "Введите номер машины: ");
};