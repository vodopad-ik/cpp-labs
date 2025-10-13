#pragma once
#include <iostream>
#include <string>
#include <string_view>

class Utils {
private:

  static bool isValidCharacter(unsigned char c);
  static bool processCyrillicCharacter(std::string_view str, size_t &i);
  static bool validateStringCharacters(std::string_view str,
                                       bool &hasMeaningfulChars);

public:
  static void clearInputBuffer();
  static void clearScreen();
  static bool isCyrillicChar(unsigned char c);
  static std::string inputOnlyLetters(const std::string &message = "");
  static int inputInt(const std::string &message = "");
  static int
  inputIntInRange(const std::string &message = "Введите число: ",
                  int min_value = 0, int max_value = 100,
                  const std::string &errorMessage =
                      "Число вне допустимого диапазона. Попробуйте снова: ");

  Utils() = delete;
  ~Utils() = delete;
};