#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class Utils {
public:
    static double input(const std::string& message = "");
    static std::string inputString(const std::string& message = "");
    static double stringToDouble(const std::string& str);
    
private:
    Utils() = delete;
};