#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

// Специализированное исключение для стека
class StackEmptyException : public std::runtime_error {
public:
    StackEmptyException() : std::runtime_error("Stack is empty") {}
};

template <typename T> 
class Stack {
private:
  struct Node {
    T data;
    // std::unique_ptr обеспечивает автоматическое управление памятью для следующего узла
    std::unique_ptr<Node> next = nullptr;
    
    explicit Node(const T &value) : data(value) {}
  };

  std::unique_ptr<Node> top_node = nullptr;
  size_t size_ = 0;

public:
  Stack() = default;
  
  // Деструктор (Участие в управлении ресурсами)
  // Поскольку top_node - это std::unique_ptr, его деструктор автоматически
  // удалит всю цепочку узлов. Мы используем = default для явного определения.
 ~Stack() {
    clear(); // Явно очищаем стек
}
  
  Stack(std::initializer_list<T> init) {
    for (const auto& item : init) {
      push(item);
    }
  }

  // Правило пяти: Конструктор копирования
  Stack(const Stack &other) {
    if (!other.empty()) {
      Stack<T> temp;
      // Копирование узлов в обратном порядке (temp - это временный стек)
      const Node *current = other.top_node.get();
      while (current) {
        temp.push(current->data);
        current = current->next.get();
      }
      
      // Перенос элементов из temp в *this (восстановление правильного порядка)
      while (!temp.empty()) {
        push(temp.top()); 
        temp.pop();
      }
    }
  }
  
  // Правило пяти: Оператор присваивания копированием (идиома copy-and-swap)
  Stack &operator=(const Stack &other) {
    if (this != &other) {
      clear(); // Очистка текущего содержимого
      Stack<T> temp(other); // Создание копии
      *this = std::move(temp); // Использование оператора перемещения
    }
    return *this;
  }
  
  // Правило пяти: Конструктор перемещения
  Stack(Stack &&other) noexcept 
    : top_node(std::move(other.top_node)), 
      size_(other.size_) 
  {
    other.size_ = 0;
  }
  
  // Правило пяти: Оператор присваивания перемещением
  Stack &operator=(Stack &&other) noexcept {
    if (this != &other) {
      top_node = std::move(other.top_node);
      size_ = other.size_;
      other.size_ = 0;
    }
    return *this;
  }

  // Основные операции
  
  void push(const T &value) {
    auto new_node = std::make_unique<Node>(value);
    new_node->next = std::move(top_node);
    top_node = std::move(new_node);
    size_++;
  }

  void pop() {
    if (empty()) {
      throw StackEmptyException();
    }
    top_node = std::move(top_node->next);
    size_--;
  }

  T &top() {
    if (empty()) {
      throw StackEmptyException();
    }
    return top_node->data;
  }
  
  const T &top() const {
    if (empty()) {
      throw StackEmptyException();
    }
    return top_node->data;
  }

  bool empty() const {
    return top_node == nullptr;
  }

  size_t size() const {
    return size_;
  }

  void clear() {
    top_node.reset(); 
    size_ = 0;
  }

  // Итераторы (без изменений)
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
      if (current) current = current->next.get();
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const Iterator &other) const = default;
  };

  // Константный итератор
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
      if (current) current = current->next.get();
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const ConstIterator &other) const = default;
  };

  Iterator begin() { return Iterator(top_node.get()); }
  Iterator end() { return Iterator(nullptr); }

  ConstIterator begin() const { return ConstIterator(top_node.get()); }
  ConstIterator end() const { return ConstIterator(nullptr); }
  ConstIterator cbegin() const { return ConstIterator(top_node.get()); }
  ConstIterator cend() const { return ConstIterator(nullptr); }
};