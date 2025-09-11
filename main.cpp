#include <iostream>
#include <locale>
#include "matrix.hpp"
#include "menu.hpp"
using namespace std;

int main() {
  setlocale(LC_ALL, "Rus");
  Matrix item1;
  Matrix item2;
  Matrix item3;
  printMenu_1();
  int choice;
  int iteration=0;
  while ((choice=input())!=1 && choice) {
    cout<<"Выберите один из вариантов, представленных в меню!!!\n> ";
  }
  while(choice){
    iteration < 2 ? printMenu_2(): printMenu_3();
    while ((choice=input()) < 0 && choice>3) {
    cout<<"Выберите один из вариантов, представленных в меню!!!\n> ";
    }
    switch (choice) {
  case 1:
    if(iteration<2){
      cout << "Введите количество строк матрицы: ";
      int size_1=input();
      cout << "Введите количество столбцов матрицы: ";
      int size_2=input();      
      if(!iteration){
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