#pragma once
#include "stack.hpp"
#include <algorithm>
#include <functional>
//#include <vector>

template <typename T> class StackAlgorithms {
public:
  // Линейный поиск
  static typename Stack<T>::Iterator linearSearch(Stack<T> &stack,
                                                  const T &value);
  // Сортировка пузырьком
  static void bubbleSort(Stack<T> &stack);
  // Проверка отсортированности
  static bool isSorted(const Stack<T> &stack);
  // Поиск минимального элемента
  static typename Stack<T>::Iterator findMin(Stack<T> &stack);
  // Поиск максимального элемента
  static typename Stack<T>::Iterator findMax(Stack<T> &stack);
};

// Реализация методов Algorithms
template <typename T>
typename Stack<T>::Iterator StackAlgorithms<T>::linearSearch(Stack<T> &stack,
                                                             const T &value) {
  for (auto it = stack.begin(); it != stack.end(); ++it) {
    if (*it == value) {
      return it;
    }
  }
  return stack.end();
}

template <typename T> void StackAlgorithms<T>::bubbleSort(Stack<T> &stack) {
  if (stack.empty() || stack.size() == 1)
    return;

  bool swapped;
  do {
    swapped = false;
    auto it1 = stack.begin();
    auto it2 = stack.begin();
    ++it2;

    while (it2 != stack.end()) {
      if (*it1 > *it2) {
        std::swap(*it1, *it2);
        swapped = true;
      }
      ++it1;
      ++it2;
    }
  } while (swapped);
}

template <typename T> bool StackAlgorithms<T>::isSorted(const Stack<T> &stack) {
  if (stack.empty() || stack.size() == 1)
    return true;

  auto it1 = stack.begin();
  auto it2 = stack.begin();
  ++it2;

  while (it2 != stack.end()) {
    if (*it1 > *it2) {
      return false;
    }
    ++it1;
    ++it2;
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