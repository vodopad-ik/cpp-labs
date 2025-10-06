#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class InvalidInputException : public std::runtime_error {
public:
    explicit InvalidInputException(const std::string& message) 
        : std::runtime_error(message) {}
};

double input(const std::string& message = "");
std::string inputAlphanumeric(const std::string& message = "");