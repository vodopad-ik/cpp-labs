#pragma once
#include <iostream>

class Array {
private:
  int *data = nullptr;
  int length = 0;

public:
  Array();
  explicit Array(int size);
  ~Array();
  Array(const Array &other);

  int getLength() const;
  int *getData() const;
  
 friend Array operator|(const Array &lhs, const Array &rhs) {
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

  Array &operator=(Array other);
  void fill();
  friend int placeElement(Array &item, int index);
  friend void print(const Array &item);
};

