#pragma once
#include <string>

class Utils {
public:
  static void clearScreen();
  static int inputInteger(const std::string &message = "");
  static double inputDouble(const std::string &message = "");
  static int
  positiveInputInteger(const std::string &message = "", int max_value = 0,
                       const std::string &errorMessage =
                           "Внимание! Введите положительное число: ");
  static double
  positiveInputDouble(const std::string &message = "", double max_value = 0.0,
                      const std::string &errorMessage =
                          "Внимание! Введите положительное число: ");
  static std::string inputOnlyLetters(const std::string &message = "");

private:
  Utils() = delete;
  ~Utils() = delete;
};