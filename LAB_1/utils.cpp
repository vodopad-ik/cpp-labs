#include <iostream>
#include <limits>
#include "utils.hpp"
using namespace std;

int input(){
    int number;
      while (true) {
        cin >> number;
        if (cin.fail() || cin.peek() != '\n') {
            cout << "Некорректный ввод. Пожалуйста, введите только целое число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }
    return number;
  }