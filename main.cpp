#include <iostream>
#include <locale>
#include "matrix.hpp"
using namespace std;

#define PRINT_MENU_1 cout<< "________________________________________________________________________\n";\
  cout<< "| МЕНЮ:                                                                |\n";\
  cout<< "|----------------------------------------------------------------------|\n";\
  cout<< "|'0' - выход;                                                          |\n";\
  cout<< "|'1' - создать пустую матрицу;                                         |\n";\
  cout<< "|______________________________________________________________________|\n> ";

#define PRINT_MENU_2 cout<< "\n________________________________________________________________________\n"; \
                   cout<< "| МЕНЮ:                                                                |\n"; \
                   cout<< "|----------------------------------------------------------------------|\n"; \
                   cout<< "|'0' - выход;                                                          |\n"; \
                   cout<< "|'1' - заполнить матрицу;                                              |\n"; \
                   cout<< "|'2' - вывод текущей матрицы на экран;                                 |\n"; \
                   cout<< "|'3' - добавить новую матрицу;                                         |\n"; \
                   cout<< "|______________________________________________________________________|\n> ";

#define PRINT_MENU_3 cout<< "\n________________________________________________________________________\n";\
  cout<< "| МЕНЮ:                                                                |\n";\
  cout<< "|----------------------------------------------------------------------|\n";\
  cout<< "|'0' - выход;                                                          |\n";\
  cout<< "|'1' - вычитание двух последних матриц(от первой вторую);              |\n";\
  cout<< "|'2' - вывод текущей матрицы на экран;                                 |\n";\
  cout<< "|'3' - вычитание двух последних матриц(от второй первую);              |\n";\
  cout<< "|______________________________________________________________________|\n> ";

int main() {
  setlocale(LC_ALL, "Rus");
  Matrix item1, item2, item3;
  PRINT_MENU_1
  int choice, iteration=0;
  while ((choice=input())!=1 && choice) {
    cout<<"Выберите один из вариантов, представленных в меню!!!\n> ";
  }
  while(choice){
    //cout<<"MАТРИЦА 'А  "
    if(iteration<2){
      PRINT_MENU_2
    }
    else {PRINT_MENU_3}
    while ((choice=input()) < 0 && choice>3) {
    cout<<"Выберите один из вариантов, представленных в меню!!!\n> ";
    }
    switch (choice) {
  case 1:
      if(iteration<2){
        cout << "Введите размеры матрицы: [";
        int size_1 = input();
        cout << "033[F033[K";
        cout << "Введите размеры матрицы: [" << size_1 << "][";
        int size_2 = input();
        cout << "033[F033[K";
        cout << "Введите размеры матрицы: [" << size_1 << "]["<< size_2 << "]\n";
        if(iteration==0){
          item1=Matrix(size_1, size_2);
          item1.fill();
        }
        else if(iteration==1){
          item2=Matrix(size_1, size_2);
          item2.fill();
        }
      }
      else item3=item1.subtract(item2);
    break;
  case 2:
    if(iteration==0) item1.print();
    else if(iteration==1) item2.print();
    else if(iteration>=2) item3.print();
    break;
  case 3:
    iteration++;
    if(iteration>=2){
      item3=item2.subtract(item1);
    }
    break;
  default:
      return 0;
    }
  }
  return 0;
}