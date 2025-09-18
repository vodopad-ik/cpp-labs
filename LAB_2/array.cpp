#include "array.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;

Array::Array() : data(nullptr), length(0) {}
Array::Array(int size) : data(nullptr), length(0) {
    if (size > 0) {
        length = size;
        data = new int[length]();
    }
}
Array::~Array() {
  delete[] data;
  data = nullptr;
}

Array::Array(const Array &other) : length(other.length) {
  data = new int[length];
  for (int i = 0; i < length; i++) {
    data[i] = other.data[i];
  }
}

int Array::getLength() const { return length; }
int* Array::getData() const { return data; }

Array operator|(const Array &lhs, const Array &rhs) {
  int lhs_len = lhs.getLength();
  int rhs_len = rhs.getLength();

  if (lhs_len == 0)
    return rhs;
  if (rhs_len == 0)
    return lhs;

  if (lhs.getData() == nullptr || rhs.getData() == nullptr) {
    return Array();
  }

  Array res(lhs_len + rhs_len);
  for (int i = 0; i < lhs.length; i++) {
    res.data[i] = lhs.data[i];
  }
  for (int j = 0; j < rhs.length; j++) {
    res.data[lhs.length + j] = rhs.data[j];
  }
  return res;
}

Array &Array::operator=(Array other) {
  if (this != &other) {
    delete[] data;
    length = other.length;
    data = other.data;
    other.data = nullptr;
    other.length = 0;
  }
  return *this;
}

void Array::fill() {
    if (data == nullptr || length == 0) {
        cout << "Ошибка: массив не инициализирован!" << endl;
        return;
    }
  cout << "\nПожалуйста заполните массив: \n\n";
  for (int i = 0; i < length; i++) {
    cout << "Введите целое число(элемент[" << i + 1 << "]): ";
    placeElement(*this, i);
  }
}