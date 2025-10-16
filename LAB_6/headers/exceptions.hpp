#pragma once
#include <stdexcept>
#include <string>

// Базовое исключение для математических операций
class MathException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;  // Наследуем все конструкторы
};

// Исключения для парсера уравнений
class ParserException : public MathException {
public:
    using MathException::MathException;  // Наследуем все конструкторы
};

class InvalidEquationException : public ParserException {
public:
    using ParserException::ParserException;  // Наследуем все конструкторы
};

class InvalidCharacterException : public ParserException {
public:
    using ParserException::ParserException;  // Наследуем все конструкторы
};

class InvalidNumberFormatException : public ParserException {
public:
    using ParserException::ParserException;  // Наследуем все конструкторы
};

// Исключения для математических операций
class MathOperationException : public MathException {
public:
    using MathException::MathException;  // Наследуем все конструкторы
};

class ZeroCoefficientException : public MathOperationException {
public:
    explicit ZeroCoefficientException(const std::string& variable = "a")
        : MathOperationException("Коэффициент " + variable + " не может быть равен нулю") {}
};

class StackEmptyException : public MathException {
public:
    StackEmptyException() : MathException("Stack is empty") {}
};

// Исключения для ввода/вывода
class IOException : public MathException {
public:
    using MathException::MathException;  // Наследуем все конструкторы
};