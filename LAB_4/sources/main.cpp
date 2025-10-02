#include "cat.hpp"
#include "dog.hpp"
#include "human.hpp"
#include "menu.hpp"
#include "program.hpp"
#include "utils.hpp"
#include <iostream>
#include <locale>
using std::cout;

int main() {
  setlocale(LC_ALL, "Rus");
  int choice = 0;
  Program program;
  cout << "Выберите объект для создания: \n";
  printMenu();
  while ((choice = inputInteger()) != 0 && program.run(choice)) {
    cout << "Выберите объект для создания: \n";
    printMenu();
  }
  return 0;
}