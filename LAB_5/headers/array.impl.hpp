#pragma once

#include "array.decl.hpp"
#include "utils.hpp"
#include <iostream>
using std::cout, std::endl;

template <class T> Array<T>::Array(size_t length) : length(length) {
  data = new T[length]();
}

template <class T> Array<T>::Array(const Array &other) : length(other.length) {
  data = new T[length];
  for (size_t i = 0; i < length; i++)
    data[i] = other.data[i];
}

template <class T>
Array<T>::Array(Array &&other) noexcept
    : data(other.data), length(other.length) {
  other.data = nullptr;
  other.length = 0;
}

template <class T> Array<T>::~Array() {
  delete[] data;
  data = nullptr;
}

template <class T> T &Array<T>::operator[](size_t index) {
  if (index >= length)
    return data[length - 1];
  return data[index];
}

template <class T> const T &Array<T>::operator[](size_t index) const {
  if (index >= length)
    return data[length - 1];
  return data[index];
}

template <class T> Array<T> &Array<T>::operator=(const Array &other) {
  if (this != &other) {
    delete[] data;
    length = other.length;
    data = new T[length];

    for (size_t i = 0; i < length; i++)
      data[i] = other.data[i];
  }
  return *this;
}

template <class T> Array<T> &Array<T>::operator=(Array &&other) noexcept {
  if (this != &other) {
    delete[] data;
    data = other.data;
    length = other.length;
    other.data = nullptr;
    other.length = 0;
  }
  return *this;
}

template <class T> size_t Array<T>::getLength() const { return length; }
template <class T> void Array<T>::setLength(size_t new_length) {
  if (new_length == length)
    return;
  T *new_data = new T[new_length]();
  size_t min_length = (new_length < length) ? new_length : length;
  for (size_t i = 0; i < min_length; i++)
    new_data[i] = data[i];

  delete[] data;
  data = new_data;
  length = new_length;
}

template <class T> void Array<T>::fill(const T &value, size_t index) {
  if (!data || !length) {
    size_t new_length = inputSize("Внимание! Массив не инициализирован. Введите "
                                "размер массива, чтобы продолжить: ");
    setLength(new_length);
  }
  if (index >= length)
    (*this)[length - 1] = value;
  else
    (*this)[index] = value;
}

  template <class T> void Array<T>::print() const {
    if (!data) {
      cout << "\nМассив пуст...\n";
      return;
    }
    cout << "[";
    for (size_t i = 0; i < length; i++) {
      cout << (*this)[i];
      if (i < length - 1)
        cout << ", ";
    }
    cout << "]" << endl;
  }

  template <class T> void Array<T>::print(size_t index) const {
    if (!data || !length) {
      cout << "\nМассив пуст...\n";
      return;
    } else if (index >= length)
      cout << "Элемент с индексом " << index << " не существует...";
    cout << "arr[" << index << "] = " << (*this)[index] << endl;
  }
