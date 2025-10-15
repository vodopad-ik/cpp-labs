#pragma once

#include <iostream>
#include <memory>

template <typename T> class Stack {
private:
  struct Node {
    T data;
    std::unique_ptr<Node> next;
    Node(const T &value) : data(value), next(nullptr) {}
  };
  std::unique_ptr<Node> top_node;
  size_t size_;

public:
  Stack() : top_node(nullptr), size_(0) {}
  Stack(std::initializer_list<T> init);

  Stack(const Stack &other);
  Stack &operator=(const Stack &other);
  Stack(Stack &&other) noexcept = default;
  Stack &operator=(Stack &&other) noexcept = default;
  ~Stack() = default;

  void push(const T &value);
  void pop();
  T &top();
  const T &top() const;
  bool empty() const;
  size_t size() const;
  void clear();

  class Iterator {
  private:
    Node *current;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    explicit Iterator(Node *node) : current(node) {}

    T &operator*() const { return current->data; }
    T *operator->() const { return &current->data; }

    Iterator &operator++() {
      if (current)
        current = current->next.get();
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }

    bool operator!=(const Iterator &other) const { return !(*this == other); }
  };

  class ConstIterator {
  private:
    const Node *current;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;

    explicit ConstIterator(const Node *node) : current(node) {}

    const T &operator*() const { return current->data; }
    const T *operator->() const { return &current->data; }

    ConstIterator &operator++() {
      if (current)
        current = current->next.get();
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const ConstIterator &other) const {
      return current == other.current;
    }

    bool operator!=(const ConstIterator &other) const {
      return !(*this == other);
    }
  };

  Iterator begin() { return Iterator(top_node.get()); }
  Iterator end() { return Iterator(nullptr); }

  ConstIterator begin() const { return ConstIterator(top_node.get()); }
  ConstIterator end() const { return ConstIterator(nullptr); }
};

template <typename T>
Stack<T>::Stack(std::initializer_list<T> init) : top_node(nullptr), size_(0) {
  for (auto it = init.begin(); it != init.end(); ++it) {
    push(*it);
  }
}

template <typename T>
Stack<T>::Stack(const Stack &other) : top_node(nullptr), size_(0) {
  if (!other.empty()) {
    Stack<T> temp;
    const Node *current = other.top_node.get();
    while (current) {
      temp.push(current->data);
      current = current->next.get();
    }
    while (!temp.empty()) {
      push(temp.top());
      temp.pop();
    }
  }
}

template <typename T> Stack<T> &Stack<T>::operator=(const Stack &other) {
  if (this != &other) {
    clear();
    Stack<T> temp(other);
    *this = std::move(temp);
  }
  return *this;
}

template <typename T> void Stack<T>::push(const T &value) {
  auto new_node = std::make_unique<Node>(value);
  new_node->next = std::move(top_node);
  top_node = std::move(new_node);
  size_++;
}

template <typename T> void Stack<T>::pop() {
  if (empty()) {
    throw std::runtime_error("Stack is empty");
  }
  top_node = std::move(top_node->next);
  size_--;
}

template <typename T> T &Stack<T>::top() {
  if (empty()) {
    throw std::runtime_error("Stack is empty");
  }
  return top_node->data;
}

template <typename T> const T &Stack<T>::top() const {
  if (empty()) {
    throw std::runtime_error("Stack is empty");
  }
  return top_node->data;
}

template <typename T> bool Stack<T>::empty() const {
  return top_node == nullptr;
}

template <typename T> size_t Stack<T>::size() const { return size_; }

template <typename T> void Stack<T>::clear() {
  while (!empty()) {
    pop();
  }
}