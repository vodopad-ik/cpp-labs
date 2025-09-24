#include "../headers/array.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;

Array::Array(int size) {
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
int *Array::getData() const { return data; }

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
    data[i] = input();
  }
}