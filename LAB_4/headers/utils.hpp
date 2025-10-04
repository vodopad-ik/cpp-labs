#pragma once
#include <string>
using std ::string;

void clearScreen();
int inputInteger(const string &message = "");
double inputDouble(const string &message = "");
int positiveInputInteger(
    const string &message = "", int max_value = 0,
    const string &errorMessage = "Внимание! Введите положительное число: ");
double positiveInputDouble(
    const string &message = "", double max_value = 0.0,
    const string &errorMessage = "Внимание! Введите положительное число: ");
string inputOnlyLetters(const string &message = "");