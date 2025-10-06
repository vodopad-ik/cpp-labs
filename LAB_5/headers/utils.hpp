#pragma once
#include <string>
using std ::string;

void clearScreen();
void clearInputBuffer();

int inputInteger(const string &message = "");
double inputDouble(const string &message = "");
size_t inputSize(const string &message, bool allow_zero = false);
int positiveInputInteger(
    const string &message = "", int max_value = 0,
    const string &errorMessage = "Внимание! Введите положительное число: ");
double positiveInputDouble(
    const string &message = "", double max_value = 0.0,
    const string &errorMessage = "Внимание! Введите положительное число: ");
string inputString(const string &message = "");