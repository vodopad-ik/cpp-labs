#pragma once
#include <stdexcept>
#include <string>

class MathException : public std::runtime_error {
public:
    explicit MathException(const std::string& message) 
        : std::runtime_error(message) {}
};

class ParserException : public MathException {
public:
    explicit ParserException(const std::string& message) 
        : MathException("Ошибка парсера: " + message) {}
};

class InvalidEquationException : public ParserException {
public:
    explicit InvalidEquationException(const std::string& message) 
        : ParserException("Некорректное уравнение: " + message) {}
};

class InvalidCharacterException : public ParserException {
public:
    explicit InvalidCharacterException(const std::string& message) 
        : ParserException("Недопустимые символы: " + message) {}
};

class InvalidNumberFormatException : public ParserException {
public:
    explicit InvalidNumberFormatException(const std::string& message) 
        : ParserException("Некорректный числовой формат: " + message) {}
};

class MathOperationException : public MathException {
public:
    explicit MathOperationException(const std::string& message) 
        : MathException("Ошибка математической операции: " + message) {}
};

class ZeroCoefficientException : public MathOperationException {
public:
    explicit ZeroCoefficientException(const std::string& variable = "a") 
        : MathOperationException("Коэффициент " + variable + " не может быть равен нулю") {}
};

class StackEmptyException : public MathException {
public:
    StackEmptyException() 
        : MathException("Stack is empty") {}
};

class IOException : public MathException {
public:
    explicit IOException(const std::string& message) 
        : MathException("Ошибка ввода/вывода: " + message) {}
};