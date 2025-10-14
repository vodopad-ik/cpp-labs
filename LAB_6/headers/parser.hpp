#pragma once
#include <regex>
#include <stdexcept>
#include <string>

class Parser {
private:
  Parser() = delete;
  static void validateAllowedChars(const std::string &str);
  static std::string simplifyString(const std::string &str);
  static void validateBasicStructure(const std::string &simplified);
  static void validateRegexPatterns(const std::string &str);
  static void validateDigitsAndDots(const std::string &str);
  static void validateDotPosition(const std::string &str, size_t pos);
  
  static void parseA(std::string &simplified, double &a);
  static void parseB(std::string &simplified, double &b);
  static void parseC(std::string &simplified, double &c_val);
  static double parseNumber(const std::string &num_str,
                            double default_value = 1.0);
  static bool isAFound(const std::string &simplified);
  static bool isValidNumber(const std::string &str);

public:
  static std::string validateEquationString(const std::string &str);
  static void parseEquationString(const std::string &equationStr, double &a,
                                  double &b, double &c);
};