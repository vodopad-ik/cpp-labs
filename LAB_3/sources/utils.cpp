#include <iostream>
#include <limits>
#include <string>
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