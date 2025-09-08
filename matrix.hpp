#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
 private:
  int **data;
  int rows;
  int cols;
  
 public:
  Matrix();
  Matrix(int a, int b);
  ~Matrix();
  void fill();
  void print();
  Matrix subtract(Matrix item);
  Matrix(const Matrix& other);
};

int input();

#endif