#include "program.hpp"
#include "menu.hpp"
#include "utils.hpp"
#include <iostream>
using std::cout;

Human Program::useObjectHuman() const {
  const string name = inputOnlyLetters("Введите имя человека: ");
  int age = positiveInputInteger("Введите возраст: ");
  const string status = inputOnlyLetters(
      "Введите социальный статус человека (например, школьник, сотрудник, "
      "пенсионер и т.п.): ");
  Human person(name, age, status);
  person.describe();
  return person;
}

Dog Program::useObjectDog() const {
  const string name = inputOnlyLetters("Введите имя собачки/песика: ");
  int age = positiveInputInteger("Введите возраст: ");
  double weight = positiveInputDouble("Введите вес(кг): ");
  const string breed =
      inputOnlyLetters("Введите его породу (например, бульдог, хаски, "
                       "ретривер и т.п.): ");
  Dog dog(name, age, weight, breed);
  dog.describe();
  return dog;
}
Cat Program::useObjectCat() const {
  const string name = inputOnlyLetters("Введите имя котика/кошки: ");
  int age = positiveInputInteger("Введите возраст: ");
  double weight = positiveInputDouble("Введите вес(кг): ");
  const string color = inputOnlyLetters("Введите оттенок шерсти: ");
  Cat cat(name, age, weight, color);
  cat.describe();
  return cat;
}

bool Program::run(int choice) const{
  switch (choice) {
  case 0:
    return false;
  case 1: {
    useObjectHuman();
    printMenu_1();
    while ((choice = inputInteger()) != 0 && choice != 1) {
      cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
    }
    if (!choice)
      return false;
    break;
  }
  case 2: {
    Dog dog = useObjectDog();
    while (true) {
      printMenu_2();
      while ((choice = inputInteger()) < 0 || choice > 2) {
        cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
      }
      if (!choice)
        return false;
      else if (choice == 1)
        dog.voice();
      else
        return true;
    }
  }
  case 3: {
    Cat cat = useObjectCat();
    while (true) {
      printMenu_3();
      while ((choice = inputInteger()) < 0 || choice > 2) {
        cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
      }
      if (!choice)
        return false;
      else if (choice == 1)
        cat.voice();
      else
        return true;
    }
  }
  default:
    cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
    return true;
  }
  return true;
}