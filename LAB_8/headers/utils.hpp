#pragma once
#include <iostream>
#include <string>
#include <string_view>

class Utils {
public:
  static void clearInputBuffer();
  static void clearScreen();
  static int inputInt(const std::string &message = "");
  static bool inputInt(int &result, const std::string &message = "");
  static int
  inputIntInRange(const std::string &message = "Введите число: ",
                  int min_value = 0, int max_value = 100,
                  const std::string &errorMessage =
                      "Число вне допустимого диапазона. Попробуйте снова: ");

  Utils() = delete;
  ~Utils() = delete;
};