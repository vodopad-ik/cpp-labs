#include "../headers/matrix.hpp"
#include "../headers/utils.hpp"
#include <format>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

void Matrix::swap(Matrix &other) noexcept {
  std::swap(rows, other.rows);
  std::swap(cols, other.cols);
  std::swap(data, other.data);
}

Matrix::Matrix() : data(nullptr), rows(0), cols(0) {}
Matrix::Matrix(int a, int b) : rows(a), cols(b) {
  if (a <= 0 || b <= 0) {
    rows = 0;
    cols = 0;
    data = nullptr;
  }
  data = new int *[rows];
  for (int i = 0; i < rows; i++) {
    data[i] = new int[cols]();
  }
}

Matrix::~Matrix() {
  if (data) {
    for (int i = 0; i < rows; i++) {
      delete[] data[i];
    }
    delete[] data;
    data = nullptr;
  }
}

Matrix::Matrix(const Matrix &other) : rows(other.rows), cols(other.cols) {
  data = new int *[rows];
  for (int i = 0; i < rows; ++i) {
    data[i] = new int[cols];
    for (int j = 0; j < cols; ++j) {
      data[i][j] = other.data[i][j];
    }
  }
}

Matrix &Matrix::operator=(Matrix other) {
  this->swap(other);
  return *this;
}

void Matrix::fill() {
  cout << "\nПожалуйста заполните матрицу: \n\n";
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << "Введите целое число(элемент[" << i + 1 << "][" << j + 1
           << "]): ";
      data[i][j] = input();
    }
  }
}

void Matrix::print() const {
  if (!rows || !cols) {
    cout << "\nПолученная матрица пуста.\n";
    return;
  }
  cout << "\nПолученная матрица: \n\n";
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << " " <<data[i][j];
    }
    cout << endl;
  }
}

Matrix Matrix::subtract(const Matrix item) const {
  if (this->cols != item.cols || this->rows != item.rows) {
    cout << "Вычитание невозможно, т.к. матрицы разных размеров.\n";
    return Matrix();
  }
  Matrix result(this->rows, this->cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result.data[i][j] = this->data[i][j] + item.data[i][j];
    }
  }
  return result;
}