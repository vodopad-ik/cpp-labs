#include "program.hpp"
#include "utils.hpp"
#include <iostream>
using std::cout;

Human Program::useObjectHuman() const {
  const string name = Utils::inputOnlyLetters("Введите имя человека: ");
  int age = Utils::positiveInputInteger("Введите возраст: ", 150, "Внимание! Введите корректное значение, т.к. люди столько не живут. ");
  const string status = Utils::inputOnlyLetters(
      "Введите социальный статус человека (например, школьник, сотрудник, "
      "пенсионер и т.п.): ");
  Human person(name, age, status);
  person.describe();
  return person;
}

Dog Program::useObjectDog() const {
  const string name = Utils::inputOnlyLetters("Введите имя собачки/песика: ");
  int age = Utils::positiveInputInteger("Введите возраст: ", 40, "Внимание! Введите корректоное значение, т. к. данный возраст не допустим для данного объекта. ");
  double weight = Utils::positiveInputDouble("Введите вес(кг): ", 155.6, "Внимание! Введите корректное значение, т. к. данный вес не допустим для данного объекта. ");
  const string breed =
      Utils::inputOnlyLetters("Введите его породу (например, бульдог, хаски, "
                       "ретривер и т.п.): ");
  Dog dog(name, age, weight, breed);
  dog.describe();
  return dog;
}
Cat Program::useObjectCat() const {
  const string name = Utils::inputOnlyLetters("Введите имя котика/кошки: ");
  int age = Utils::positiveInputInteger("Введите возраст: ", 40, "Внимание! Введите корректное значение, т. к. данный возраст не допустим для данного объекта. ");
  double weight = Utils::positiveInputDouble("Введите вес(кг): ", 22.5, "Внимание! Введите корректное значение, т. к. данный вес не допустим для данного объекта. ");
  const string color = Utils::inputOnlyLetters("Введите оттенок шерсти: ");
  Cat cat(name, age, weight, color);
  cat.describe();
  return cat;
}

bool Program::handleHumanCase() const {
  useObjectHuman();
  printMenu_1();
  int choice = getValidChoice(0, 1);
  return choice != 0;
}

bool Program::handleDogCase() const {
  Dog dog = useObjectDog();
  while (true) {
    printMenu_2();
    int choice = getValidChoice(0, 2);
    if (!choice)
      return false;
    if (choice == 1)
      dog.voice();
    else
      return true;
  }
}

bool Program::handleCatCase() const {
  Cat cat = useObjectCat();

  while (true) {
    printMenu_3();
    int choice = getValidChoice(0, 2);

    if (!choice)
      return false;
    if (choice == 1)
      cat.voice();
    else
      return true;
  }
}

int Program::getValidChoice(int min, int max) const {
  int choice;
  while ((choice = Utils::inputInteger()) < min || choice > max) {
    cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
  }
  return choice;
}

bool Program::run(int choice) const {
  switch (choice) {
  case 0:
    return false;
  case 1: 
    return handleHumanCase();
  case 2: 
   return handleDogCase();
  case 3: 
  return handleCatCase();
  default:
    cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
    return true;
  }
}