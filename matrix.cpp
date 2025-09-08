#include <iostream>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include "matrix.hpp"
using namespace std;

int input(){
    int number;
      while (true) {
        cin >> number;
        cout<<endl;
        if (cin.fail() || cin.peek() != '\n') {
            cout << "Некорректный ввод. Пожалуйста, введите только целое число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }
    return number;
  }

Matrix::Matrix()=default;
Matrix::Matrix(int a, int b): rows(a), cols(b) {
    if(a<=0 || b<=0) {
      throw invalid_argument("Не корректные размеры матрицы!");
    }
    rows=a;
    cols=b;
    data=new int*[rows];
    if(!data) {
      throw bad_alloc();
    }
    for(int i=0; i<rows;i++){
      data[i]=new int[cols]();
      if(!data[i]){
        for(int j=i; j>=0;j--) {
          delete[] data[j];
        }
        delete [] data;
        throw bad_alloc();
      }
    }
  }
Matrix::~Matrix(){
  if (data) {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        data=nullptr;
    }
}

void Matrix::fill(){
  cout<<"\nПожалуйста заполните матрицу: \n";
    for(int i=0; i<rows; i++){
      for (int j=0; j< cols; j++) {
        cout << "Введите целое число(элемент["<<i+1<<"]["<<j+1<<"]): ";
        data[i][j]=input();
      }
    }
  } 

void Matrix::print(){
  if(!rows||!cols) cout<<"Матрица пуста.\n";
  cout<<"\nПолученная матрица: \n";
  for(int i=0; i<rows; i++){
    for (int j=0; j< cols; j++) {
      cout<< setw(4)<<data[i][j]<<" ";
    }
    cout<<endl;
  }
}

Matrix Matrix::subtract(Matrix item) {
  if(this->cols!=item.cols || this->rows!=item.rows)
  {
      throw; 
  }
  Matrix result(this->rows, this->cols);
  for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++){
          result.data[i][j]=this->data[i][j]-item.data[i][j];
      }
  }
  return result; 
}

Matrix::Matrix(const Matrix& other){
  rows=other.rows;
  cols=other.cols;
  data= new int*[rows];
  for(int i=0; i<rows; i++){
    data[i]=new int[cols];
    for(int j=0; j<cols; j++){
      data[i][j]=other.data[i][j];
    }
  }
}