#include <iostream>
#include <limits>
//#include <stdexcept>
#include <iomanip>
#include <utility>
#include "matrix.hpp"
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

void Matrix::swap(Matrix& other){
  std::swap(rows, other.rows);
  std::swap(cols, other.cols);
  std::swap(data, other.data);
}

Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}
Matrix::Matrix(int a, int b): rows(a), cols(b) {
    if(a<=0 || b<=0) {
      throw invalid_argument("Не корректные размеры матрицы!");
    }
    data=new int*[rows];
    for(int i=0; i<rows;i++){
      data[i]=new int[cols]();
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

Matrix::Matrix(Matrix& other): rows(other.rows), cols(other.cols){
  data = new int*[rows];
  for (int i = 0; i < rows; ++i) {
    data[i] = new int[cols];
    for (int j = 0; j < cols; ++j) {
      data[i][j] = other.data[i][j];
    }
  }
}

Matrix& Matrix::operator=(Matrix other) {
    this->swap(other);
    return *this;
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
  if(!rows||!cols) {
    cout<<"\nПолученная матрица пуста.\n";
    return;
  }
  cout<<"\nПолученная матрица: \n";
  for(int i=0; i<rows; i++){
    for (int j=0; j< cols; j++) {
      cout<< setw(4)<<data[i][j]<<" ";
    }
    cout<<endl;
  }
}

Matrix Matrix::subtract(Matrix item) {
  if(this->cols!=item.cols || this->rows!=item.rows) {
    cout<<"Вычитание невозможно, т.к. матрицы разных размеров.\n";
    return Matrix();
  }
  Matrix result(this->rows, this->cols);
  for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++){
          result.data[i][j]=this->data[i][j]-item.data[i][j];
      }
  }
  return result; 
}