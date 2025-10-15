#pragma once
#include "stack.hpp"

template <typename T> class StackAlgorithms {
public:
  static typename Stack<T>::Iterator linearSearch(Stack<T> &stack,
                                                  const T &value);
  static void bubbleSort(Stack<T> &stack);
  static bool isSorted(const Stack<T> &stack);
  static typename Stack<T>::Iterator findMin(Stack<T> &stack);
  static typename Stack<T>::Iterator findMax(Stack<T> &stack);
};

template <typename T>
typename Stack<T>::Iterator StackAlgorithms<T>::linearSearch(Stack<T> &stack,
                                                             const T &value) {
  for (auto i = stack.begin(); i != stack.end(); i++) {
    if (*i == value)
      return i;
  }
  return stack.end();
}

template <typename T> void StackAlgorithms<T>::bubbleSort(Stack<T> &stack) {
  if (stack.empty() || stack.size() == 1)
    return;

  bool swapped;
  do {
    swapped = false;
    auto i1 = stack.begin();
    auto i2 = stack.begin();
    i2++;

    while (i2 != stack.end()) {
      if (*i1 > *i2) {
        std::swap(*i1, *i2);
        swapped = true;
      }
      ++i1;
      ++i2;
    }
  } while (swapped);
}

template <typename T> bool StackAlgorithms<T>::isSorted(const Stack<T> &stack) {
  if (stack.empty() || stack.size() == 1)
    return true;

  auto i1 = stack.begin();
  auto i2 = stack.begin();
  ++i2;

  while (i2 != stack.end()) {
    if (*i1 > *i2) {
      return false;
    }
    ++i1;
    ++i2;
  }
  return true;
}

template <typename T>
typename Stack<T>::Iterator StackAlgorithms<T>::findMin(Stack<T> &stack) {
  if (stack.empty())
    return stack.end();

  auto min_it = stack.begin();
  for (auto it = stack.begin(); it != stack.end(); ++it) {
    if (*it < *min_it) {
      min_it = it;
    }
  }

  return min_it;
}

template <typename T>
typename Stack<T>::Iterator StackAlgorithms<T>::findMax(Stack<T> &stack) {
  if (stack.empty())
    return stack.end();

  auto max_it = stack.begin();
  for (auto it = stack.begin(); it != stack.end(); ++it) {
    if (*it > *max_it) {
      max_it = it;
    }
  }

  return max_it;
}