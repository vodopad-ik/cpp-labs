#include "program.hpp"
#include "array.decl.hpp"
#include "array.impl.hpp"
#include "utils.hpp"

int Program::getValidChoice(int min, int max) const {
  int choice;
  while ((choice = Utils::inputInteger()) < min || choice > max) {
    cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
  }
  return choice;
}

template <typename T> Array<T> Program::createArr(int &choice) {
  printMenu_1();
  choice = getValidChoice(0, 2);
  if (choice == 2) {
    size_t length = Utils::inputSize("Введите размер массива: ");
    return Array<T>(length);
  }
  return Array<T>();
}

template <typename T>
bool Program::useTypeArr(function<T(const string &)> inputFunc) {
  int choice;
  Array<T> arr = createArr<T>(choice);
  if (!choice)
    return false;
  while (true) {
    printMenu_2();
    choice = getValidChoice(0, 4);
    switch (choice) {
    case 0:
      return false;
    case 1: {
      T value = inputFunc("Введите значение: ");
      size_t index = Utils::inputSize("Введите индекс элемента в массиве: ", true);
      arr.fill(value, index);
      break;
    }
    case 2: {
      size_t index = Utils::inputSize("Введите индекс элемента в массиве: ", true);
      arr.print(index);
      break;
    }
    case 3: {
      size_t length = arr.getLength();
      if (!length) {
        length = Utils::inputSize("Внимание! Массив не инициализирован. Введите "
                           "размер массива, чтобы продолжить: ");
        arr.setLength(length);
      }
      for (size_t i = 0; i < length; i++) {
        cout << "Введите элемент[" << i << "]: ";
        arr.fill(inputFunc(""), i);
      }
      break;
    }
    case 4: {
      arr.print();
      break;
    }
    default:
      cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
    }
  }
}

bool Program::run(int choice) {
  switch (choice) {
  case 0:
    return false;
  case 1:
    return useTypeArr<int>(Utils::inputInteger);
  case 2:
    return useTypeArr<double>(Utils::inputDouble);
  case 3:
    return useTypeArr<string>(
        [](const string &msg) { return Utils::inputString(msg); });
  default:
    cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
  }
  return true;
}