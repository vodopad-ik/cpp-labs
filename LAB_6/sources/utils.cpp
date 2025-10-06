#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include "utils.hpp"
using namespace std;

double input(const string& message) {
    if (!message.empty()) {
        cout << message;
    }

    double number;
    while (true) {
        cin >> number;
        if (cin.fail() || cin.peek() != '\n') {
            cout << "Некорректный ввод. Пожалуйста, введите число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return number;
}

string inputAlphanumeric(const string& message) {
    if (!message.empty()) {
        cout << message;
    }

    string input;
    getline(cin, input);

    // Проверка на пустую строку
    if (input.empty()) {
        throw InvalidInputException("Введена пустая строка. Допустимы только цифры и латинские символы.");
    }

    // Проверка каждого символа
    for (char c : input) {
        if (!isalnum(static_cast<unsigned char>(c))) {
            string error_msg = "Обнаружен недопустимый символ: '";
            error_msg += c;
            error_msg += "'. Допустимы только цифры и латинские символы (a-z, A-Z, 0-9).";
            throw InvalidInputException(error_msg);
        }
    }

    return input;
}