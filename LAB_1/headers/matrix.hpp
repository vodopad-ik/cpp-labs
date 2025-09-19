#pragma once

class Matrix {
private:
  int **data;
  int rows;
  int cols;
  void swap(Matrix &other) noexcept;

public:
  Matrix();
  Matrix(int a, int b);
  ~Matrix();
  Matrix(const Matrix &other);
  Matrix &operator=(Matrix other);
  void fill();
  void print() const;
  Matrix subtract(const Matrix item) const;
};