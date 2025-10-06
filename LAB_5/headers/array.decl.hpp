#pragma once
#include <cstddef>

template <typename T> class Array {
private:
  T *data = nullptr;
  size_t length = 0;

public:
  Array() = default;
  explicit Array(size_t length);
  Array(const Array &other);
  Array(Array &&other) noexcept;

  ~Array();

  T &operator[](size_t index);
  const T &operator[](size_t index) const;
  Array &operator=(const Array &other);
  Array &operator=(Array &&other) noexcept;

  size_t getLength() const;
  void setLength(size_t new_length);
  void fill();
  void fill(const T &value, size_t index);
  void print() const;
  void print(size_t index) const;
};