#include "../headers/array.hpp"
#include "../headers/menu.hpp"
#include "../headers/utils.hpp"
#include <iostream>
#include <locale>
using namespace std;

int main() {
  setlocale(LC_ALL, "Rus");
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
      return 0;
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
        return 0;
      }
      else if (iteration >= 2) 
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
  return 0;
}