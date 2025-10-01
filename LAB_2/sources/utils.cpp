#include "utils.hpp"
#include "array.hpp"
#include "menu.hpp"
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

void program() {
  Array item1;
  Array item2;
  Array item3;
  printMenu_1();
  int choice;
  int iteration = 0;
  while ((choice = input()) != 1 && choice)
    cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
  while (choice) {
    iteration < 2 ? printMenu_2() : printMenu_3();
    switch (choice = input()) {
    case 0:
      return;
    case 1:
      if (iteration == 0) {
        int length = positiveInput("Введите количество элементов массива: ");
        item1 = Array(length);
        item1.fill();
      } else if (iteration == 1) {
        int length = positiveInput("Введите количество элементов массива: ");
        item2 = Array(length);
        item2.fill();
      } else
        item3 = item1 | item2;
      break;
    case 2:
      if (iteration == 0)
        print(item1);
      else if (iteration == 1)
        print(item2);
      else if (iteration >= 2 && item3.getLength()) {
        print(item3);
        return;
      } else if (iteration >= 2)
        print(item3);
      break;
    case 3:
      if (iteration++ >= 2)
        cout << "Выберите один из вариантов, представленных в меню!!!\n";
      break;
    default:
      cout << "Выберите один из вариантов, представленных в меню!!!\n";
    }
  }
}
