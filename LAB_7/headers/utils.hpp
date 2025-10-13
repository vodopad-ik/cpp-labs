#pragma once
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

class Utils {
private:
  static void clearInputBuffer();

  static bool isValidCharacter(unsigned char c);
  static bool processCyrillicCharacter(const std::string& str, size_t& i);
  static bool validateStringCharacters(const std::string& str, bool& hasMeaningfulChars);

public:
  static void clearScreen();
  static bool isCyrillicChar(unsigned char c);
  static std::string inputOnlyLetters(const std::string &message = "");
  static int inputIntegerInRange(
      const string &message = "Введите число: ", int min_value = 0,
      int max_value = 100,
      const string &errorMessage =
          "Число вне допустимого диапазона. Попробуйте снова: ");

  Utils() = delete;
  ~Utils() = delete;
};