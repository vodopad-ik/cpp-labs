#pragma once
#include <iostream>

class Array {
private:
  int *data = nullptr;
  int length = 0;
  int count = 0;

public:
  Array() = default;
  explicit Array(int size);
  ~Array();
  Array(const Array &other);

  int getLength() const;
  int *getData() const;

  Array createUniqueArray(Array &unique) const;
  int countRepeatingElements(int val) const;

  friend Array operator|(const Array &arr1, const Array &arr2) {
    int arr1_len = arr1.length;
    int arr2_len = arr2.length;
    if (arr1_len == 0)
      return arr2;
    if (arr2_len == 0)
      return arr1;

    Array res(arr1_len + arr2_len);
    Array unique(arr1_len + arr2_len);
    arr1.createUniqueArray(unique);
    arr2.createUniqueArray(unique);

    for (int u = 0; u < unique.count; u++) {
      int val = unique.data[u];
      int repeat_arr1 = arr1.countRepeatingElements(val);
      int repeat_arr2 = arr2.countRepeatingElements(val);

      int count = (repeat_arr1 > repeat_arr2) ? repeat_arr1 : repeat_arr2;

      for (int c = 0; c < count; c++)
        res.data[res.count++] = val;
    }

    Array finalRes(res.count);
    for (int i = 0; i < res.count; i++)
      finalRes.data[i] = res.data[i];
    return finalRes;
  }

  Array &operator=(Array other);
  void fill();
  friend void print(const Array &item);
  friend void input(const Array &item);
};
