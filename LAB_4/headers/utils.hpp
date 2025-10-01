#pragma once
#include <string>
using std ::string;

void clearScreen();
int inputInteger(const string &message = "");
double inputDouble(const string &message = "");
int positiveInputInteger(const string &message = "");
double positiveInputDouble(const string &message = "");
string inputOnlyLetters(const string &message = "");