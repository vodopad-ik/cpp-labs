#include "menu.hpp"
#include <iostream>
using std ::cout;

void printMenu() {
  cout << SOLID_LINE;
  cout << "| МЕНЮ:                                                             "
          "   |\n";
  cout << BROKEN_DIVIDING_LINE;
  cout << "|'0' - выход;                                                       "
          "   |\n";
  cout << "|'1' - добавить автомобиль в файл;                                  "
          "   |\n";
  cout << "|'2' - показать все автомобили из файла;                            "
          "   |\n";
  cout << "|'3' - найти количество машин по году выпуска;                      "
          "   |\n";

  cout << SOLID_DIVIDING_LINE;
}

void printMenu_1() {
  cout << SOLID_LINE;
  cout << "| МЕНЮ:                                                             "
          "   |\n";
  cout << BROKEN_DIVIDING_LINE;
  cout << "|'0' - выход;                                                       "
          "   |\n";
  cout << "|'1' - продолжить добавление авто;                                  "
          "   |\n";
  cout << SOLID_DIVIDING_LINE;
}
