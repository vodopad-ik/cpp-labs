#pragma once

class Array {
private:
  int *data;
  int length;

public:
  // Конструктор по умолчанию
  Array();

  // Конструктор с размером
  explicit Array(int size);

  // Деструктор
  ~Array();

  // Конструктор копирования
  Array(const Array &other);

  // Перегруженный оператор | для объединения массивов
  friend Array operator|(const Array &lhs, const Array &rhs);

  // Перегруженный оператор присваивания с идиомой copy-and-swap
  Array &operator=(Array other);

  // Заполняет массив данными от пользователя
  void fill();

  // Дружественные функции для операций ввода-вывода
  friend std::ostream &operator<<(std::ostream &os, const Array &item);
  friend std::istream &operator>>(std::istream &is, Array &item);
  
  // Геттеры
  int getLength() const;
  int *getData() const;
<<<<<<< HEAD
};
=======
  
  friend Array operator|(const Array &lhs, const Array &rhs);
  Array &operator=(Array other);
  void fill();
  friend int placeElement(Array &item, int index);
  friend void print(const Array &item);
};
>>>>>>> recover-commit
