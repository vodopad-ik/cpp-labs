#include "carValidNumber.hpp"
#include "program.hpp"
#include "utils.hpp"

int Program::getValidChoice(int min, int max) const {
  int choice;
  while ((choice = Utils::inputInteger()) < min || choice > max) {
    cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
  }
  return choice;
}

bool Program::run(int choice) {
  CarManager manager("cars.dat");
  switch (choice) {
  case 0:
    return false;
  case 1: {
    string plate = CarNumber::inputLicensePlate("Введите номер машины: ");
    cout << "Введите год выпуска: ";
    int year = Utils::inputIntegerInRange("", 1900, 2025, "Внимание! Год должен быть в интервале от 1900 до 2025 года.");
    string color = Utils::inputOnlyLetters("Введите оттенок кузова: ");
 
    Car newCar(plate, year, color);
    if (manager.addCar(newCar)) {
        cout << "Машина успешно добавлена!" << std::endl;
        newCar.display();
    } else {
        cout << "Ошибка: не удалось добавить машину!" << std::endl;
    }
    break;
  }
  case 2: {
    cout << "\nВсе машины в файле:" << std::endl;
    manager.reset();
    Car car;
    int count = 0;

    while (manager.readNextCar(car)) {
        cout << ++count << ". ";
        car.display();
    }

    if (count == 0) {
        cout << "Файл пуст или не существует!" << std::endl;
    }
    break;
  }
  case 3: {
    int year = Utils::inputIntegerInRange("Введите год выпуска для поиска: ", 1900, 2025, "Год должен быть от 1900 до 2025.");
    int count = manager.countCarsByYear(year);
    cout << "Количество машин " << year << " года выпуска: " << count << std::endl;
    break;
  }
  default:
    cout << "Выберите один из вариантов, представленных в меню!!!\n> ";
  }
  return true;
}