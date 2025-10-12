#pragma once
#include <iostream>
#include <string>

class CarNumber {
private:
  static const std::string validLetters;
  static const std::string validDigits;

  static bool isValidDigit(char c);
  static bool isValidLetter(char c);
  static void displayTemplate();

public:
  static std::string
  inputLicensePlate(const std::string &message = "Введите номер машины: ");
};