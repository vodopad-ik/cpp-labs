#include "array.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm> // Для std::swap

// using namespace std; - Удалено для более явного использования std::

Array::Array() : data(nullptr), length(0) {}

<<<<<<< HEAD
Array::Array(int size) {
  if (size > 0) {
    length = size;
    data = new int[length]();
  } else {
    data = nullptr;
    length = 0;
  }
=======
Array::Array() : data(nullptr), length(0) {}
Array::Array(int size) : data(nullptr), length(0) {
    if (size > 0) {
        length = size;
        data = new int[length]();
    }
>>>>>>> recover-commit
}

Array::~Array() {
  delete[] data;
<<<<<<< HEAD
}

Array::Array(const Array &other) : length(other.length), data(nullptr) {
    if (other.data != nullptr && other.length > 0) {
        data = new int[length];
        std::copy(other.data, other.data + length, data);
    }
}

// Перегруженный оператор | для объединения массивов
=======
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

>>>>>>> recover-commit
Array operator|(const Array &lhs, const Array &rhs) {
  if (lhs.getData() == nullptr) {
    return Array(rhs);
  }
  if (rhs.getData() == nullptr) {
    return Array(lhs);
  }

  int lhs_len = lhs.getLength();
  int rhs_len = rhs.getLength();
<<<<<<< HEAD
  
  Array res(lhs_len + rhs_len);

  int *res_data = res.getData();
  const int *lhs_data = lhs.getData();
  const int *rhs_data = rhs.getData();

  for (int i = 0; i < lhs_len; ++i) {
    res_data[i] = lhs_data[i];
  }
  for (int j = 0; j < rhs_len; ++j) {
    res_data[lhs_len + j] = rhs_data[j];
=======

  if (lhs_len == 0)
    return rhs;
  if (rhs_len == 0)
    return lhs;

  if (lhs.getData() == nullptr || rhs.getData() == nullptr) {
    return Array();
  }
//fffr
  Array res(lhs_len + rhs_len);
  for (int i = 0; i < lhs.length; i++) {
    res.data[i] = lhs.data[i];
  }
  for (int j = 0; j < rhs.length; j++) {
    res.data[lhs.length + j] = rhs.data[j];
>>>>>>> recover-commit
  }

  return res;
}

// Оператор присваивания с идиомой copy-and-swap
Array &Array::operator=(Array other) {
  std::swap(data, other.data);
  std::swap(length, other.length);
  return *this;
}

void Array::fill() {
<<<<<<< HEAD
  if (data == nullptr || length == 0) {
    std::cout << "Ошибка: массив не инициализирован или имеет нулевой размер!" << std::endl;
    return;
  }
  std::cout << "\nПожалуйста, заполните массив: \n\n";
  for (int i = 0; i < length; ++i) {
    std::cout << "Введите целое число (элемент[" << i + 1 << "]): ";
    // Используем дружественную функцию
    if (placeElement(*this, i) == 0) {
      std::cout << "Ошибка при заполнении элемента. Прекращение заполнения." << std::endl;
      break;
    }
=======
    if (data == nullptr || length == 0) {
        cout << "Ошибка: массив не инициализирован!" << endl;
        return;
    }
  cout << "\nПожалуйста заполните массив: \n\n";
  for (int i = 0; i < length; i++) {
    cout << "Введите целое число(элемент[" << i + 1 << "]): ";
    placeElement(*this, i);
>>>>>>> recover-commit
  }
}

int Array::getLength() const { 
    return length; 
}

int *Array::getData() const { 
    return data; 
}

std::ostream &operator<<(std::ostream &os, const Array &item) {
  if (item.length == 0) {
    return os << "\nМассив пуст...\n";
  }
  os << "\n[";
  for (int i = 0; i < item.length; ++i) {
    os << item.data[i];
    if (i < item.length - 1) {
      os << ", ";
    }
  }
  os << "]\n";
  return os;
}

std::istream &operator>>(std::istream &is, Array &item) {
  std::cout << "Введите количество элементов массива: ";
  int newLength = positiveInput("");
  item.length = newLength;
  delete[] item.data;
  item.data = new int[newLength]();
  item.fill();
  return is;
}
