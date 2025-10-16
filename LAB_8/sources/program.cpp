#include "program.hpp"
#include "algorithms.hpp"
#include "utils.hpp"
#include <iostream>

int Program::getValidChoice(int min, int max) const {
  return Utils::inputIntInRange(
      "", min, max, "Выберите один из вариантов, представленных в меню!!!\n> ");
}

Stack<int> Program::inputStack() const {
  Stack<int> stack;
  std::cout
      << "Введите элементы стека (целые числа). "
      << "Для завершения ввода введите пустую строку (просто нажмите Enter):\n";

  int count = 0;
  while (true) {
    int value;
    if (bool success = Utils::inputInt(
            value, "Введите число (или Enter для завершения): ");
        !success) {
      std::cout << "Ввод завершен.\n";
      break;
    }
    stack.push(value);
    count++; 
    std::cout << "Элемент " << value << " добавлен в стек.\n";
  }
  if (count == 0)
    std::cout << "Не было введено чисел.\n";
  else
    std::cout << "Добавлено " << count << " элементов в стек.\n";
  return stack;
}

void Program::printStack(const Stack<int> &stack,
                         const std::string &message) const {
  if (!message.empty()) {
    std::cout << message;
  }
  for (const auto &item : stack) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

void Program::run() const {
  Stack<int> stack = inputStack();
  if (stack.empty()) {
    std::cout << "Стек пуст.\n";
    return;
  }
  std::cout << "\n" << SOLID_LINE;
  std::cout << "ТЕКУЩИЙ СТЕК: ";
  printStack(stack);
  printMenu();
  int choice = 0;
  while ((choice = Utils::inputInt()) != 0) {
    switch (choice) {
    case 0:
      return;
    case 1: {
      int search_value = Utils::inputInt("\nВведите элемент для поиска: ");
      if (auto search_result =
              StackAlgorithms<int>::linearSearch(stack, search_value);
          search_result != stack.end()) {
        std::cout << "Элемент " << search_value << " найден в стеке!\n";
      } else {
        std::cout << "Элемент " << search_value << " не найден в стеке.\n";
      }
      break;
    }
    case 2: {
      StackAlgorithms<int>::bubbleSort(stack);

      std::cout << "ОТСОРТИРОВАННЫЙ СТЕК: ";
      printStack(stack);
      if (StackAlgorithms<int>::isSorted(stack)) {
        std::cout << "Стек отсортирован корректно!\n";
      } else {
        std::cout << "Ошибка: стек не отсортирован!\n";
      }
      break;
    }
    default:
      std::cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
    }
    printMenu();
  }
}