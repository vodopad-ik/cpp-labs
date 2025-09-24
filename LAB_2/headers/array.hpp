#pragma once
#include <iostream>

class Array {
private:
  int *data = nullptr;
  int length = 0;

public:
  Array() = default;
  explicit Array(int size);
  ~Array();
  Array(const Array &other);

  int getLength() const;
  int *getData() const;

  friend Array operator|(const Array &arr1, const Array &arr2) {
    int arr1_len = arr1.getLength();
    int arr2_len = arr2.getLength();
    if (arr1_len == 0)
      return arr2;
    if (arr2_len == 0)
      return arr1;
    if (arr1.getData() == nullptr || arr2.getData() == nullptr) {
      return Array();
    }

    Array res(arr1_len + arr2_len);
    int k = 0;

    Array unique(arr1_len + arr2_len);
    int uniqueCount = 0;

    for (int i = 0; i < arr1_len; i++) {
      bool exists = false;
      for (int j = 0; j < uniqueCount; j++) {
        if (unique.data[j] == arr1.data[i]) {
          exists = true;
          break;
        }
      }
      if (!exists)
        unique.data[uniqueCount++] = arr1.data[i];
    }

    for (int i = 0; i < arr2_len; i++) {
      bool exists = false;
      for (int j = 0; j < uniqueCount; j++) {
        if (unique.data[j] == arr2.data[i]) {
          exists = true;
          break;
        }
      }
      if (!exists) {
        unique.data[uniqueCount++] = arr2.data[i];
      }
    }

    for (int u = 0; u < uniqueCount; u++) {
      int val = unique.data[u];
      int countArr1 = 0, countArr2 = 0;

      for (int i = 0; i < arr1_len; i++) {
        if (arr1.data[i] == val)
          countArr1++;
      }
      for (int j = 0; j < arr2_len; j++) {
        if (arr2.data[j] == val)
          countArr2++;
      }
      int count = (countArr1 > countArr2) ? countArr1 : countArr2;

      for (int c = 0; c < count; c++) {
        res.data[k++] = val;
      }
    }

    Array finalRes(k);
    for (int i = 0; i < k; i++) {
      finalRes.data[i] = res.data[i];
    }
    return finalRes;
  }

  Array &operator=(Array other);
  void fill();
  friend void print(const Array &item);
};