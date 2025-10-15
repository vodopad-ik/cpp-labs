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
  cout << "|'1' - поиск по стеку;                                              "
          "   |\n";
  cout << "|'2' - сортировка стека;                                            "
          "   |\n";
  cout << SOLID_DIVIDING_LINE;
}