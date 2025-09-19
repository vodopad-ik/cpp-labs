#include "../headers/utils.hpp"
#include <iostream>
#include <limits>

int input(const std::string& message) {
    if (!message.empty()) {
        std::cout << message;
    }
    
    int number;
    while (true) {
        std::cin >> number;
        if (std::cin.fail() || std::cin.peek() != '\n') {
            std::cout << "Некорректный ввод. Пожалуйста, введите только целое число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return number;
}

int positiveInput(const std::string& message) {
    int value;
    do {
        if (!message.empty()) {
            std::cout << message;
        }
        value = input();
        if (value <= 0) {
            std::cout << "Внимание! Введите целое положительное число: ";
        }
    } while (value <= 0);
    return value;
}