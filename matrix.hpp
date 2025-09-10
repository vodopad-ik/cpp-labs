#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
 private:
  int **data;
  int rows;
  int cols;
  void swap(Matrix& other);
  
 public:
  Matrix();
  Matrix(int a, int b);
  ~Matrix();
  Matrix(Matrix& other);
  Matrix& operator=(Matrix other);
  void fill();
  void print();
  Matrix subtract(Matrix item);
};

int input();

#endif