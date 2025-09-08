#include <iostream>
#include "matrix.hpp"
using namespace std;

int main(){
  cout<<"Введите размеры первой матрицы:" ;
  Matrix item1(input(),input());
  cout<<"Введите размеры второй матрицы:" ;
  Matrix item2(input(),input());
  item1.print();
  item1.fill();
  item1.print();
  item2.print();
  item2.fill();
  item2.print();
  
  Matrix res=item1.subtract(item2);
  res.print();
  return 0;
}