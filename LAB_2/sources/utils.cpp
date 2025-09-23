#include "../headers/utils.hpp"
#include "array.hpp"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int input(const string &message) {
  if (!message.empty()) {
    cout << message;
  }
  int number;
  while (true) {
    cin >> number;
    if (cin.fail() || cin.peek() != '\n') {
      cout << "Некорректный ввод. Пожалуйста, введите только целое число.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      break;
    }
  }
  return number;
}

int positiveInput(const string &message) {
  int value;
  do {
    if (!message.empty()) {
      cout << message;
    }
    value = input();
    if (value <= 0) {
      cout << "Внимание! Введите целое положительное число: ";
    }
  } while (value <= 0);
  return value;
}

int placeElement(Array &item, int index) {
  if (index >= item.getLength() || index < 0) {
    cout << "Несуществующая ячейка!!!";
    return 0;
  }
  return item.getData()[index] = input();
}

void print(const Array &item) {
  if (item.getLength() == 0) {
    cout << "\nМассив пуст...\n";
    return;
  }
  cout << "\n[";
  for (int i = 0; i < item.getLength(); ++i) {
    cout << item.getData()[i];
    if (i < item.getLength() - 1) {
      cout << ", ";
    }
  }
  cout << "]\n";
}
