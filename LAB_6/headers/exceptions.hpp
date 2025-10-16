#pragma once
#include <stdexcept>
#include <string>

class MathException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class ParserException : public MathException {
public:
    using MathException::MathException;
};

class InvalidEquationException : public ParserException {
public:
    using ParserException::ParserException;
};

class InvalidCharacterException : public ParserException {
public:
    using ParserException::ParserException;
};

class InvalidNumberFormatException : public ParserException {
public:
    using ParserException::ParserException;
};

class MathOperationException : public MathException {
public:
    using MathException::MathException;
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

class IOException : public MathException {
public:
    using MathException::MathException; 
};