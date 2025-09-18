#pragma once
#include "array.hpp"
#include <string>

int input(const std::string &message = "");
int positiveInput(const std::string &message = "");
int placeElement(Array &item, int index);
void print(const Array &item);