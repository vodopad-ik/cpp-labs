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
  cout << "|'1' - cоздать массив на основе шаблона типа <int>;                 "
          "   |\n";
  cout << "|'2' - cоздать массив на основе шаблона типа <double>;              "
          "   |\n";
  cout << "|'3' - cоздать массив на основе шаблона типа <char>;                "
          "   |\n";
  cout << "|'4' - cоздать массив на основе шаблона типа <str>;                 "
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
  cout << "|'1' - coздать массив выбранного типа по умолчанию;                 "
          "   |\n";
  cout << "|'2' - coздать массив выбранного типа с указазанным размером;       "
          "   |\n";
  cout << SOLID_DIVIDING_LINE;
}

void printMenu_2() {
  cout << SOLID_LINE;
  cout << "| МЕНЮ:                                                             "
          "   |\n";
  cout << BROKEN_DIVIDING_LINE;
  cout << "|'0' - выход;                                                       "
          "   |\n";
  cout << "|'1' - ввод определенного элемента массива выбранного типа;         "
          "   |\n";
  cout << "|'2' - вывод определенного элемента массива выбранного типа;        "
          "   |\n";
  cout << "|'3' - ввести массив выбранного типа;                               "
          "   |\n";
  cout << "|'4' - вывести массив выбранного типа;                              "
          "   |\n";
  cout << SOLID_DIVIDING_LINE;
}
